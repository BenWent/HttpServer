#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

#include "CMyTCPClientObserver.h"

using namespace std;

CMyTCPClientObserver:: CMyTCPClientObserver()
{
}

CMyTCPClientObserver:: ~CMyTCPClientObserver()
{
}

void CMyTCPClientObserver:: redirect(char* ip, int port, string content)
{
	// 建立客户端Socket,使用ipv4协议通信，使用scoket字节流传输数据
	int nClientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == nClientSocket)
	{
		cout << strerror(errno) << endl;
	    cout << "socket error" << endl;

	    return;
	}

	// IPV4套接口地址结构
	sockaddr_in ServerAddress;
	memset(&ServerAddress, 0, sizeof(sockaddr_in));

	// 设置 协议簇字段
	ServerAddress.sin_family = AF_INET;

	// 设置 服务端ip地址字段
	if(::inet_pton(AF_INET, ip, &ServerAddress.sin_addr) != 1)
	{
		cout << strerror(errno) << endl;
	    cout << "inet_pton error" << endl;
	    ::close(nClientSocket);

	    return;
	}

	// 设置 服务端端口字段
	ServerAddress.sin_port = htons(port);

	// 客户端调用该函数向服务端发出连接请求
	if(::connect(nClientSocket, (sockaddr*)&ServerAddress, sizeof(ServerAddress)) == -1)
	{
		cout << strerror(errno) << endl;
	    cout << "redirect error" << endl;
	    ::close(nClientSocket);

	    return;
	}

	::write(nClientSocket, content.c_str(), content.length());
	char buff[100];
	int len = ::read(nClientSocket, buff, sizeof(buff));
	buff[len] = '\0';

	cout << "从服务器 [" << ip << "] 收到消息: " << buff << endl;
}


void CMyTCPClientObserver:: ClientFunction(int nConnectedSocket, int port)
{
	string content;
	cout << "请输入信息:";
	cin >> content;

	::write(nConnectedSocket, content.c_str(), content.length());

	char buff[16];
	int len = ::read(nConnectedSocket, buff, sizeof(buff));
	buff[len] = '\0';

	cout << "重定向到 " << buff << endl;
	redirect(buff, port, content);
}
