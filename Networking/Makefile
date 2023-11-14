CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=server.cpp
SERVER_OBJECTS=$(filter server.o, $(SOURCES:.cpp=.o))


.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(SERVER_OBJECTS)
