OBJ = main.c
LIBONE = ./src/calcs.c
LIBTWO = ./src/calcs.h
FLAG = -lGL -lglut -lGLU -lm 


all:  clean create build run fill

clean:
	rm -rf bin

create:
	mkdir bin

build:
	gcc -o bin/project $(OBJ) $(LIBONE) $(LIBTWO) $(FLAG)

run: 
	./bin/project

fill:
	rm bin/project
