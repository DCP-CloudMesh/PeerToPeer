TYPE := PROVIDER

CXX = g++ 
CXXFLAGS = -std=c++17 -Wall -D"${TYPE}"

# List of source files
COMMON_SRCS = main.cpp Networking/Server/server.cpp Networking/Client/client.cpp Peers/Peer/peer.cpp
PROVIDER_SRCS =  Peers/Provider/provider.cpp  
REQUESTER_SRCS = Peers/Peer/peer

# Object files for the common code and each executable
COMMON_OBJS = $(COMMON_SRCS:.cpp=.o)
PROVIDER_OBJS = $(PROVIDER_SRCS:.cpp=.o)
REQUESTER_OBJS = $(REQUESTER_SRCS:.cpp=.o)

# Output binary names
PROVIDER_EXEC = provider.out
REQUESTER_EXEC = requester.out

all: $(PROVIDER_EXEC) $(REQUESTER_EXEC)

provider: TYPE := PROVIDER
requester: TYPE := REQUESTER
	

$(PROVIDER_EXEC): $(COMMON_OBJS) $(PROVIDER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	${MAKE} selective-clean

$(REQUESTER_EXEC): $(COMMON_OBJS) $(REQUESTER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	${MAKE} selective-clean

.PHONY: clean

selective-clean:
	rm -f *.o 
clean:
	rm -f *.o $(PROVIDER_EXEC) $(REQUESTER_EXEC) 
