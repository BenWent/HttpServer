INCLUDE=../include
OBJS=Main.o Config.o CMyTCPClientObserver.o CTCPClient.o

OUTPUT=client

CC=g++ -g

main: $(OBJS) $(OBJS_CLIENT)
	$(CC) -o $(OUTPUT) $(OBJS)
Config.o: $(INCLUDE)/Config.cpp
	$(CC) -c $(INCLUDE)/Config.cpp
CTCPClient.o: CTCPClient.cpp
	$(CC) -c CTCPClient.cpp
CMyTCPClientObserver.o: CMyTCPClientObserver.cpp
	$(CC) -c CMyTCPClientObserver.cpp
Main.o: Main.cpp
	$(CC) -c Main.cpp
clean:
	rm -f $(OUTPUT) $(OBJS)
