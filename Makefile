CXX = g++

COMMON_FLAGS = -msse4.1 -mpclmul -Wall -Werror -Wpedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -Ofast

SRC_DIR = src
BIN_DIR = bin

INCLUDES = -Ivendor/fpng

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(INCLUDES)/*.cpp)
BINARY = $(BIN_DIR)/RTIAW

.PHONY: all debug release clean

all: release

release: FLAGS = $(RELEASE_FLAGS) $(COMMON_FLAGS)
release: $(BINARY)

debug: FLAGS = $(DEBUG_FLAGS) $(COMMON_FLAGS)
debug: $(BINARY)

$(BINARY): $(SOURCES)
	$(CXX) $(FLAGS) $(VENDOR) -o $@ $^

clean:
	rm -f $(BINARY)