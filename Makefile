CXX = c++

CFLAGS = -Wall -Werror -Wpedantic -msse4.1 -mpclmul -std=c++23 -fopenmp -fno-exceptions
ifeq ($(MAKECMDGOALS), release)
	CFLAGS += -O3 -DNDEBUG
endif

SRC_DIR = src
BIN_DIR = bin

MATERIALS_DIR = src/Materials
FPNG_DIR = vendor/fpng

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp $(FPNG_DIR)/*.cpp $(MATERIALS_DIR)/*.cpp)
OBJ_FILES = $(patsubst %.cpp, $(BIN_DIR)/%.o, $(SRC_FILES))

INCL = -Isrc -Ivendor/fpng -Ivendor/glm

TARGET = $(BIN_DIR)/rtk

.PHONY: all release clean

all: $(TARGET)

release: all

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CFLAGS) -o $@ $^

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCL)

clean:
	rm -f $(TARGET) $(OBJ_FILES)
