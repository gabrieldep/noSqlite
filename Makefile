CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -I src
LDFLAGS ?=

BIN     := nosqlite
BUILD   := build

SRCS := \
	apps/cli/main.c \
	src/core/storage/page_manager.c \
	src/core/memory/page_table/page_table.c \
	src/core/memory/buffer_pool/buffer_pool.c

OBJS := $(SRCS:%.c=$(BUILD)/%.o)

TEST_SRCS := \
	tests/memory/page_table/page_table_test.c \
	src/core/memory/page_table/page_table.c

PKG_CONFIG_PATH ?= /usr/local/lib/pkgconfig
export PKG_CONFIG_PATH

CRITERION_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRITERION_LIBS := $(shell pkg-config --libs criterion 2>/dev/null)

.PHONY: all clean test test-debug

all: $(BUILD)/$(BIN)

test: $(BUILD)/page_table_test
	./$(BUILD)/page_table_test --verbose

test-debug: CFLAGS += -g -O0
test-debug: $(BUILD)/page_table_test
	./$(BUILD)/page_table_test --verbose

$(BUILD)/$(BIN): $(OBJS) | $(BUILD)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD)/page_table_test: $(TEST_SRCS) | $(BUILD)
	$(CC) $(CFLAGS) $(CRITERION_CFLAGS) -o $@ $(TEST_SRCS) $(CRITERION_LIBS)

$(BUILD)/%.o: %.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
