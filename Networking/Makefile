TYPE := SERVER
# Makefile for compiling server.cpp

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRCS = server.cpp

# Header files
HDRS = server.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = server

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
