CXX = g++

COMMON_FLAGS = -fopenmp -msse4.1 -mpclmul -Wall -Werror -Wpedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -Ofast

SRC_DIR = src
BIN_DIR = bin

FPNG_DIR = vendor/fpng
INCLUDES = -I$(FPNG_DIR) -Ivendor/glm

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(FPNG_DIR)/*.cpp)
BINARY = $(BIN_DIR)/Raytracing

.PHONY: all debug release clean

all: release

release: FLAGS := $(RELEASE_FLAGS) $(COMMON_FLAGS)
release: $(BINARY)

debug: FLAGS := $(DEBUG_FLAGS) $(COMMON_FLAGS)
debug: $(BINARY)

$(BINARY): $(SOURCES)
	$(CXX) $(FLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(BINARY)
