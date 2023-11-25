TYPE := CLIENT
# Makefile for compiling client.cpp

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall

# Source files
SRCS = client.cpp

# Header files
HDRS = client.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target static library
TARGET = libclient.a

# Rule to build the executable
$(TARGET): $(OBJS)
	ar rcs $@ $^

# Rule to build object files from source files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to clean up the build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
