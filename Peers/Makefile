CC=g++
CFLAGS=-c -Wall

SOURCES=peer.cpp provider.cpp requester.cpp server.cpp

PEER_OBJECTS=$(filter peer.o, $(SOURCES:.cpp=.o))
PROVIDER_OBJECTS=$(filter provider.o, $(SOURCES:.cpp=.o))
REQUESTER_OBJECTS=$(filter requester.o, $(SOURCES:.cpp=.o))
SERVER_OBJECTS=$(filter server.o, $(SOURCES:.cpp=.o))

PROVIDER_EXECUTABLE=provider.out
REQUESTER_EXECUTABLE=requester.out

all: $(PROVIDER_EXECUTABLE) $(REQUESTER_EXECUTABLE)

$(PROVIDER_EXECUTABLE): $(PROVIDER_OBJECTS)
	$(CC) $^ -o $@

$(REQUESTER_EXECUTABLE): $(REQUESTER_OBJECTS)
	$(CC) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(PROVIDER_OBJECTS) $(REQUESTER_OBJECTS) $(PROVIDER_EXECUTABLE) $(REQUESTER_EXECUTABLE)
