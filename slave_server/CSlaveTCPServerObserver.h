#ifndef CMASTERTCPSERVER_H
#define CMASTERTCPSERVER_H

#include <string>
#include <map>
#include <netinet/in.h>
#include <pthread.h>

#include "../server/CTCPServerObserver.h"

class CSlaveTCPServerObserver : public CTCPServerObserver
{
public:
    CSlaveTCPServerObserver();

    virtual ~CSlaveTCPServerObserver();

public:
    /**
		服务端回调函数
    */
    virtual void ServerFunction(int nConnectedSocket);
};

#endif
