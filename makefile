OBJ = main.c
LIBONE = ./src/calcs.c
LIBTWO = ./src/calcs.h
LIBTREE = ./src/zoom.c
LIBFOUR = ./src/zoom.h
FLAG = -lGL -lglut -lGLU -lm 


all:  clean create build run fill

clean:
	rm -rf bin

create:
	mkdir bin

build:
	gcc -o bin/project $(OBJ) $(LIBONE)  $(LIBTREE) $(LIBTWO) $(LIBFOUR) $(FLAG)

run: 
	./bin/project

fill:
	rm bin/project
