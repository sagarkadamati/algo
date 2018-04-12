build:
	gcc -finstrument-functions -g -c -o main.o main.c
	gcc -c -o trace.o trace.c
	gcc main.o trace.o -o main
run:
	./main
	cat trace.out
readlog:
	./readtracelog.sh main trace.out
clean:
	rm -rf main *.o trace.out
