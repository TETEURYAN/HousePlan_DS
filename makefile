OBJ = main.c
LIBONE = ./src/calcs.c
LIBTWO = ./src/zoom.c
LIBTREE = ./src/house.c

LIBFOUR = ./src/calcs.h
LIBFIVE = ./src/zoom.h
LIBSIX = ./src/house.h


FLAG = -lGL -lglut -lGLU -lm 


all:  clean create build run fill

clean:
	rm -rf bin

create:
	mkdir bin

build:
	gcc -o bin/project $(OBJ) $(LIBONE) $(LIBTWO) $(LIBTREE) $(LIBFOUR) $(LIBFIVE) $(LIBSIX) $(FLAG)

run: 
	./bin/project

fill:
	rm bin/project
