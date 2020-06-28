#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h> // net_ntoa函数
#include <pthread.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>

#include "../include/Config.h"
#include "CMasterTCPServerObserver.h"

using namespace std;

std:: map<std:: string, int> CMasterTCPServerObserver:: slaveCount;

CMasterTCPServerObserver:: CMasterTCPServerObserver()
{
	// 从配置文件中读取 Master所有slaves
	Config config("slaves.config"); 
	int serverNums = config.Read("slaveNums", serverNums);

	string slaveName, slaveIp;
	stringstream ss;
	for(int i=1; i <= serverNums; i++)
	{
		ss << "slave" << i;
		ss >> slaveName;

		slaveIp = config.Read(slaveName, slaveIp);
		slaveCount[slaveIp] = 0;

		ss.clear();
	}

	/* 测试是否成功读取配置文件 */
	// map<string, int>::iterator it;

	// it = slaveCount.begin();

	// while(it != slaveCount.end())
	// {
	//     cout << it->first << " = " << it->second << endl;
	//     it ++;         
	// }
}

CMasterTCPServerObserver:: ~CMasterTCPServerObserver()
{

}

void CMasterTCPServerObserver:: ServerFunction(int nListenSocket)
{
	fd_set fds;
	int maxsock;  
    struct timeval tv;

    std::vector<int> clients;
    sockaddr_in clientAddress;
	socklen_t lengthOfClientAddress = sizeof(sockaddr_in);

	// 记录轮转次数
	int count = 1;

    maxsock = nListenSocket;  
    while (1) {  
        // 初始化文件描述符集合  
        FD_ZERO(&fds);  
        FD_SET(nListenSocket, &fds);  
  
        // 超时设置  
        tv.tv_sec = 30;
        tv.tv_usec = 0;  
  
        // 将请求连接添加到 文件描述符集合 中 
        for(std::vector<int>:: iterator iter = clients.begin(); 
        		iter != clients.end(); iter++)
        {
        	FD_SET(*iter, &fds);  
        }
  
        int ret = select(maxsock + 1, &fds, NULL, NULL, &tv);  
        if (ret < 0) { // 错误发生后，就立即关闭服务
            cout << "select error" << endl;
            break;  
        } else if (ret == 0) {  
            cout << "select timeout" << endl;  
            continue;  
        }

        std::vector<int>::iterator iter = clients.begin();
        // 检查文件描述符集合中的所有文件描述符的状态
        while(iter != clients.end())
        {
        	if (FD_ISSET(*iter, &fds)) { // 当前的文件描述符 clients[i]状态是否发生变化 

                map<string, int>::iterator it = slaveCount.begin();
				std::string  ip;
				while(it != slaveCount.end()) // 负载均衡策略，轮转将请求分发给 slaves
				{
				    if(it -> second < count)
				    {
				    	ip = it -> first;
				    	slaveCount[ip] = it -> second + 1;
				    	break;
				    }
				    it++;         
				}
				if(it == slaveCount.end())
				{
					it = slaveCount.begin();
					ip = it -> first;
				    slaveCount[ip] = it -> second + 1; 

				    count = slaveCount[ip];
				}

				char buff[16];
                int len = ip.copy(buff, sizeof(buff));
                buff[len] = '\0';
                // 将slave的ip发给client，让client请求真正的服务提供者
                send(*iter, buff, sizeof(buff), 0);

                // cout << "slave ip : " << buff << endl;
				
                FD_CLR(*iter, &fds);                
                close(*iter);
                iter = clients.erase(iter); // 从vecotr删除元素时，将自动指向下一个元素
            }else{
	        	iter++;
	        }
        }
  
        // 检查是否有新的请求想建立连接  
        if (FD_ISSET(nListenSocket, &fds)) {  
            int new_fd = accept(nListenSocket, (struct sockaddr *)&clientAddress, 
            					&lengthOfClientAddress);  
            if (new_fd <= 0) {
                cout << strerror(errno) << endl;
                cerr << "accept error" << endl;  
                continue;  
            }  
  
            // 将新的请求添加到请求队列中
            clients.push_back(new_fd);
			cout << "新连接 ["  << inet_ntoa(clientAddress.sin_addr) << ":" 
                    << ntohs(clientAddress.sin_port) << "] " << "请求建连" << endl ;

			// 更新 maxsock,确保其为最大值
            if (new_fd > maxsock)  
                maxsock = new_fd;  
        } 
    }

    // 关闭所有保持的连接  
    std::vector<int>::iterator iter = clients.begin();
    while(iter != clients.end()){
        close(*iter);
        iter = clients.erase(iter);
    }
}
