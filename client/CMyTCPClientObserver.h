#ifndef CMYTCPCLIENTOBSERVER_H
#define CMYTCPCLIENTOBSERVER_H

#include <string>

#include "CTCPClientObserver.h"

class CMyTCPClientObserver : public CTCPClientObserver
{
public:
    CMyTCPClientObserver(); 
    virtual ~CMyTCPClientObserver();
    
public:
    virtual void ClientFunction(int nConnectedSocket, int port);

    /** 
    	@Summary:重定向到slave服务器 
    	@Parameters:
    		@ip:slave服务器ip
    		@port:重新开启socket的port
    		@content:重定向时附带的消息
    */
    void redirect(char* ip, int port, std::string message);
};

#endif
