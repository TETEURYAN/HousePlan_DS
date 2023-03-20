OBJ = main.c
LIBONE = ./src/calcs.c
<<<<<<< Updated upstream
LIBTWO = ./src/zoom.c
LIBTREE = ./src/house.c

LIBFOUR = ./src/calcs.h
LIBFIVE = ./src/zoom.h
LIBSIX = ./src/house.h


FLAG = -lGL -lglut -lGLU -lm 
=======
LIBTWO = ./src/house.c
LIBTHREE = ./src/drawning.c
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	gcc -o bin/project $(OBJ) $(LIBONE) $(LIBTWO) $(LIBTREE) $(LIBFOUR) $(LIBFIVE) $(LIBSIX) $(FLAG)
=======
	gcc -o bin/project $(OBJ) $(LIBONE) $(LIBTWO) $(LIBTHREE) $(LIBFOUR) $(LIBSIX) $(LIBFIVE) $(FLAG)
>>>>>>> Stashed changes

run: 
	./bin/project

fill:
	rm bin/project
