all: main
main: main.c	
	gcc -Wall -o main main.c
	
.PHONY: clean all
clean:
	rm main