# Makefile

CC = gcc
CPPFLAGS = -Wall -Wextra -MMD
CFLAGS = -Wall -Wextra -std=c99 -O3 -lm -ldl 
LDFLAGS = 
LDLIBS = `pkg-config --libs sdl` -lSDL -lSDL_image -lgd -lpng -lz -ljpeg -lfreetype -lm

SRC= main.c ../import/import.c blur.c border.c filters.c grey.c rotate.c saturation.c sym.c gdfct.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} main
	${RM} *.d
	${RM} *.o

# END
