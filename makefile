OBJ = main.c
LIBONE = ./src/calcs.c
LIBTWO = ./src/house.c
LIBTHREE = ./src/drawning.c

LIBFOUR = ./src/calcs.h
LIBFIVE = ./src/drawning.h
LIBSIX = ./src/house.h

FLAG = -lGL -lglut -lGLU -lm 

all:  clean create build run fill

clean:
	rm -rf bin

create:
	mkdir bin

build:
	gcc -o bin/project $(OBJ) $(LIBONE) $(LIBTWO) $(LIBTHREE) $(LIBFOUR) $(LIBSIX) $(LIBFIVE) $(FLAG)

run: 
	./bin/project

fill:
	rm bin/project
