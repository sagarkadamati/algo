rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

GCC := "other-gcc"

APP = $(shell basename $(shell pwd))

SRCS := $(call rwildcard,./,*.c)
SRCS += ../src/bc_tracker.c

# CFLAGS = -Wall -g
CFLAGS = -g
LINUX_LIBS = -lpthread -lrt
OTHER_LIBS = -lsocket

clean:
	@ rm -rf bin

build: clean
	@ mkdir -p bin
	@ gcc $(SRCS) $(CFLAGS) $(LINUX_LIBS) -o bin/$(APP)

buildother: clean
	@ mkdir -p bin
	@ ${GCC} $(SRCS) $(CFLAGS) $(OTHER_LIBS) -o bin/$(APP)

run: build
	@ ./bin/$(APP) &



