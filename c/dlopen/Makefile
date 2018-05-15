app = dlopen_sample
lib = libcat.so libdog.so

CFLAGS = -Wall -ansi -pedantic
LDFLAGS = -ldl

all: myapp $(lib)

lib%.so: %.c
	$(CC) -shared -fPIC $(CFLAGS) -o $@ $<

clean:
	$(RM) $(app) $(lib)

run: all
	./$(app) cat
	./$(app) dog
	-./$(app) bear

myapp:
	$(CC) $(CFLAGS) dlopen_sample.c -o $(app) $(LDFLAGS)

$(lib): animal.h
