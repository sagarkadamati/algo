rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,lib/,*.c)
SRCS += $(call rwildcard,core/,*.c)
SRCS += $(call rwildcard,init/,*.c)
SRCS += $(call rwildcard,trackers/*,*.c)

TEST += $(call rwildcard,test/,*.c)

AGENT := $(call rwildcard,lib/,*.c)
AGENT += $(call rwildcard,agent/,*.c)
AGENT += core/bc_tracker.c
AGENT += core/bc_stream.c
AGENT += trackers/heap/heap_viewer.c

APP = $(shell basename $(shell pwd))
CC = gcc
CC_X = gcc
LDFLAGS = -ldl
CFLAGS = -Wall -g
LIBS  = -lpthread -lrt
LIBS_X  = -lsocket
INCLUDE = -I./include -I./trackers

# CFLAGS = -Wall -g -finstrument-functions
all: build_agent libx

allx: build_agent build_agentx libx

lib: clean
	@ mkdir -p out/lib
	@ $(CC) $(SRCS) -shared -fPIC $(CFLAGS) $(INCLUDE) -o	 out/lib/libbctracker.so

libx: clean
	@ mkdir -p out/lib
	@ $(CC_X) $(SRCS) -shared -fPIC $(CFLAGS) $(INCLUDE) -o	 out/lib/libbctracker.so

build_app:
	@ mkdir -p out/bin
	@ $(CC) $(SRCS) $(TEST) $(CFLAGS) $(INCLUDE) $(LIBS) -o out/bin/$(APP) $(LDFLAGS)

build_agent:
	@ mkdir -p out/bin
	@ $(CC) $(AGENT) $(CFLAGS) $(INCLUDE) $(LIBS) -o out/bin/agent $(LDFLAGS)

build_agentx:
	@ mkdir -p out/bin
	@ $(CC_X) $(AGENT) $(CFLAGS) $(INCLUDE) $(LIBS_X) -o out/bin/agentx

run: build
	@ ./out/bin/$(APP)

clean:
	@ $(RM) -rf out
