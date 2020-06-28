#include <iostream>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <arpa/inet.h> // net_ntoa函数
#include <pthread.h>
#include <sys/select.h>
#include <map>

#include "CSlaveTCPServerObserver.h"

using namespace std;


#define BUFF_SIZE 100

CSlaveTCPServerObserver:: CSlaveTCPServerObserver()
{
	
}

CSlaveTCPServerObserver:: ~CSlaveTCPServerObserver()
{

}

void CSlaveTCPServerObserver:: ServerFunction(int nListenSocket)
{
	fd_set fds;
	int maxsock;  
    struct timeval tv;

    std::vector<int> clients;
    sockaddr_in clientAddress;
	socklen_t lengthOfClientAddress = sizeof(sockaddr_in);

    std::map<int, std::string> fileIpTable;

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
        		char buff[BUFF_SIZE];
               	ret = recv(*iter, buff, sizeof(buff), 0);

               	char str[] = "收到信息! 正在处理中...\n";  
                send(*iter, str, sizeof(str) + 1, 0);  
                  
                  
                if (ret <= 0) {  
                    FD_CLR(*iter, &fds);                
                    close(*iter);  

                    iter = clients.erase(iter); 
                } else { // receive data  
                    if (ret < BUFF_SIZE)  
                        memset(&buff[ret], '\0', 1);  
                    cout << "客户端 [" << fileIpTable[*iter] << "] 发送的消息是:" << buff << endl; 
                }

                fileIpTable.erase(*iter);
            }else{
	        	iter++;
	        }
        }
  
        // 检查是否有新的请求想建立连接  
        if (FD_ISSET(nListenSocket, &fds)) {  
            int new_fd = accept(nListenSocket, (struct sockaddr *)&clientAddress, 
            					&lengthOfClientAddress);  
            if (new_fd <= 0) {  
                cerr << "accept error" << endl;  
                continue;  
            }  

            std::string ip = inet_ntoa(clientAddress.sin_addr);
            int port = ntohs(clientAddress.sin_port);
  
            // 将新的请求添加到请求队列中
            clients.push_back(new_fd);
            fileIpTable[new_fd] = ip;

			cout << "新连接 ["  << ip << ":" << port << "] " 
                    << "请求建连" << endl ;

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
