#include "CSlaveTCPServerObserver.h"
#include "../server/CTCPServer.h"

int main()
{
    CSlaveTCPServerObserver observer;

    CTCPServer myserver(&observer, 4000);
    myserver.Run();
    
    return 0;
}

