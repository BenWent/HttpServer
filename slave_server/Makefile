SERVER=../server
OBJS_SERVER=SlaveServer.o CSlaveTCPServerObserver.o CTCPServer.o
OUTPUT_SERVER=SlaveServer
CC=g++ 

main: $(OBJS_SERVER)
	$(CC) -o $(OUTPUT_SERVER) $(OBJS_SERVER)
SlaveServer.o: SlaveServer.cpp
	$(CC) -c SlaveServer.cpp
CSlaveTCPServerObserver.o: CSlaveTCPServerObserver.cpp
	$(CC) -c CSlaveTCPServerObserver.cpp
CTCPServer.o: $(SERVER)/CTCPServer.cpp
	$(CC) -c $(SERVER)/CTCPServer.cpp

clean:
	rm -f  $(OUTPUT_SERVER) $(OBJS_SERVER)
