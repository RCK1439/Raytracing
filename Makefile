CXX = g++

COMMON_FLAGS = -fopenmp -msse4.1 -mpclmul -Wall -Werror -Wpedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -Ofast

SRC_DIR = src
BIN_DIR = bin

FPNG_DIR = vendor/fpng
INCLUDES = -I$(FPNG_DIR) -Ivendor/glm

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(FPNG_DIR)/*.cpp)
BINARY = $(BIN_DIR)/rtk

.PHONY: all debug release clean mkbin

all: release

release: FLAGS := $(RELEASE_FLAGS) $(COMMON_FLAGS)
release: mkbin $(BINARY)

debug: FLAGS := $(DEBUG_FLAGS) $(COMMON_FLAGS)
debug: mkbin $(BINARY)

mkbin:
	mkdir -p bin

$(BINARY): $(SOURCES)
	$(CXX) $(FLAGS) $(INCLUDES) -o $@ $^

clean:
	rm -f $(BINARY)