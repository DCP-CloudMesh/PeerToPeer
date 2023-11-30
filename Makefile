TYPE := PROVIDER
TARGET := main

CXX := g++ 
CXXFLAGS := -std=c++20 -Wall -D"${TYPE}" -o ${TARGET}

SRC_DIR := src
BUILD_DIR := build


# List of source files
SRCS := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean

# # Object files for the common code and each executable
# COMMON_OBJS = $(COMMON_SRCS:.cpp=.o)
# PROVIDER_OBJS = $(PROVIDER_SRCS:.cpp=.o)
# REQUESTER_OBJS = $(REQUESTER_SRCS:.cpp=.o)

# # Output binary names
# PROVIDER_EXEC = provider.out
# REQUESTER_EXEC = requester.out

# all: $(PROVIDER_EXEC) $(REQUESTER_EXEC)

# provider: TYPE := PROVIDER
# requester: TYPE := REQUESTER
	

# $(PROVIDER_EXEC): $(COMMON_OBJS) $(PROVIDER_OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^
# 	${MAKE} selective-clean

# $(REQUESTER_EXEC): $(COMMON_OBJS) $(REQUESTER_OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^
# 	${MAKE} selective-clean

# .PHONY: clean

# selective-clean:
# 	rm -f *.o 
# clean:
# 	rm -f *.o $(PROVIDER_EXEC) $(REQUESTER_EXEC) 
