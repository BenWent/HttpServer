SERVER=../server
INCLUDE=../include
OBJS_SERVER=MasterServer.o CMasterTCPServerObserver.o CTCPServer.o Config.o
OUTPUT_SERVER=MasterServer
CC=g++ -g

main: $(OBJS_SERVER)
	$(CC) -o $(OUTPUT_SERVER) $(OBJS_SERVER)
MasterServer.o: MasterServer.cpp
	$(CC) -c MasterServer.cpp
Config.o: $(INCLUDE)/Config.cpp
	$(CC) -c $(INCLUDE)/Config.cpp
CMasterTCPServerObserver.o: CMasterTCPServerObserver.cpp
	$(CC) -c CMasterTCPServerObserver.cpp
CTCPServer.o: $(SERVER)/CTCPServer.cpp
	$(CC) -c $(SERVER)/CTCPServer.cpp

clean:
	rm -f  $(OUTPUT_SERVER) $(OBJS_SERVER)
