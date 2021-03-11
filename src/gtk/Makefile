# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= -Wall -Wextra -MMD
CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -Wextra -std=c99 -O3 -lm -ldl 
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
LDLIBS= `pkg-config --libs gtk+-3.0` -LDLIBS -lm

SRC= main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}


clean:
	${RM} *.o
	${RM} *.d
	${RM} main
	
cleanwc:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
