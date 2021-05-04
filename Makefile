CC=gcc

CPPFLAGS= -Wall -Wextra -MMD
CFLAGS= `pkg-config --cflags gtk+-3.0 webkit2gtk-4.0` -Wall -Wextra -std=c99 -O3 -lm -ldl
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
LDLIBS= `pkg-config --libs gtk+-3.0 webkit2gtk-4.0` `pkg-config --libs sdl` -lm -lSDL_image -lgd -lpng -lz -ljpeg -lfreetype

SRC= src/main.c src/import/import.c src/operations/blur.c src/gtk/interface.c src/operations/border.c src/operations/filters.c src/operations/grey.c src/operations/rotate.c src/operations/saturation.c src/operations/sym.c src/operations/testgd.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: src/main

src/main: ${OBJ}


clean:
	${RM} src/*.o
	${RM} src/*.d
	${RM} src/main
	${RM} src/import/*.o
	${RM} src/import/*.d
	${RM} src/operations/*.o
	${RM} src/operations/*.d
	${RM} src/gtk/*.d
	${RM} src/gtk/*.o
	${RM} -r imgmodify/yourmodifyimage.bmp

# END
