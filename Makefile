CC := clang++
# TODO: Remove Wno's
CPPFLAGS ?= -std=c++20 -Wall -Wno-for-loop-analysis -Wno-unused-variable

BUILD_DIR := ./builds
BIN_DIR := ./bin
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
SRCS_WITH_SRC_STRIPPED := $(subst $(SRC_DIR)/,,$(SRCS))
OBJS := $(SRCS_WITH_SRC_STRIPPED:%=$(BUILD_DIR)/%.o)

all: evm-state-db

clear:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

evm-state-db: $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(BIN_DIR)/evm-state-db

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@
