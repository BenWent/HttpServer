#include "CMasterTCPServerObserver.h"
#include "../server/CTCPServer.h"

int main()
{
    CMasterTCPServerObserver observer;

    CTCPServer myserver(&observer, 4000);
    myserver.Run();
    
    return 0;
}

