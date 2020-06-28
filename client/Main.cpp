#include "CMyTCPClientObserver.h"
#include "CTCPClient.h"

int main()
{
	CMyTCPClientObserver observer;
    CTCPClient client(&observer);
    
    client.Run();

	return 0;
}
