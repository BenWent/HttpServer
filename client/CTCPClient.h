#ifndef CTCPCLEINT_H
#define CTCPCLEINT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <vector>
#include <iostream>

#include "CTCPClientObserver.h"


// 客户端Socket父类
class CTCPClient
{
public:
	/**
		@Summary:构造函数
		@Pamrameters:
			@nServerPort:指定服务器socket的端口
	*/
    CTCPClient(CTCPClientObserver* pOberver);

    virtual ~CTCPClient();

public:
	/**
		@Summary：连接到服务端socket
	*/
    int Run();

private:
	// 服务端Scoket使用的端口
    int m_nServerPort;
	// 服务端ip 
	char* m_strServerIP;

    CTCPClientObserver* m_pOberver;
};

#endif
