#ifndef CTCPCLIENTOBSERVER_H
#define CTCPCLIENTOBSERVER_H

class CTCPClientObserver
{
public:
    CTCPClientObserver()
    {
    }

    virtual ~CTCPClientObserver()
    {
    }

public:
	// 客户端socket要执行的功能的顶级接口
    virtual void ClientFunction(int nConnectedSocket, int port) = 0;
};

#endif
