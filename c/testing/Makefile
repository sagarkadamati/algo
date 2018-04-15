rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.c)
SRCS += $(call rwildcard,src/,*.cpp)

APP = $(shell basename $(shell pwd))
LIBS  = -lpthread -lrt
CFLAGS = -Wall

clean:
	@ rm -rf bin

build: clean
	@ mkdir bin
	@ g++ $(SRCS) $(CFLAGS) $(LIBS) -o "bin/$(APP)"

run: build
	@ ./bin/"$(APP)"
