
CFLAGS = -g -Wall 

all : tst

tst : myintrf.c myintrf.h space.c space.h object.c object.h player.c player.h world.c world.h rectangles.h rectangles.c pruebaintrf.c
	gcc $(CFLAGS) -o tst myintrf.c space.c object.c player.c world.c rectangles.c pruebaintrf.c

clean :
	rm -f tst