#ifndef CMASTERTCPSERVER_H
#define CMASTERTCPSERVER_H

#include <string>
#include <map>
#include <netinet/in.h>
#include <pthread.h>

#include "../server/CTCPServerObserver.h"

class CMasterTCPServerObserver : public CTCPServerObserver
{
public:
    CMasterTCPServerObserver();

    virtual ~CMasterTCPServerObserver();

public:
    /**
		服务端回调函数
    */
    virtual void ServerFunction(int nConnectedSocket);

private:
    // slave服务器 与 slave连接请求数 映射器
    static std:: map<std:: string, int> slaveCount;
};

#endif
