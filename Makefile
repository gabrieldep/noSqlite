CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -Wpedantic -I src
LDFLAGS ?=

BIN     := nosqlite
BUILD   := build

SRCS := \
	apps/cli/main.c \
	src/core/storage/page_manager.c \
	src/core/memory/buffer_pool.c

OBJS := $(SRCS:%.c=$(BUILD)/%.o)

.PHONY: all clean

all: $(BUILD)/$(BIN)

$(BUILD)/$(BIN): $(OBJS) | $(BUILD)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o: %.c | $(BUILD)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
