CFLAGS = -Wall -g

all:
	gcc $(CFLAGS) input/parser.c input/reader.c output/shellwriter.c state.c string_manip.c location.c free.c main.c -o program
clean:
	rm -f program