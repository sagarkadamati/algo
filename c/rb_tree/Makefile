rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,./,*.c)

APP = $(shell basename $(shell pwd))
INCLUDE = -I./src
LIBS  = -lpthread -lrt
CFLAGS = -Wall -g -rdynamic
# CFLAGS = -Wall -finstrument-functions -g

clean:
	@ rm -rf bin

build: clean
	@ mkdir bin
	@ gcc $(SRCS) $(CFLAGS) $(INCLUDE) $(LIBS) -o bin/$(APP)

run: build
	@ ./bin/$(APP)