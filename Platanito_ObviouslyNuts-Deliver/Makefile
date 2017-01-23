
CFLAGS = -g -Wall 

all : game

game : myintrf.c myintrf.h space.c space.h object.c object.h player.c player.h world.c world.h rectangles.h rectangles.c game.c game.h pruebagame.c cop.c cop.h fight.c fight.h
	gcc $(CFLAGS) -o game myintrf.c space.c object.c player.c world.c rectangles.c game.c pruebagame.c cop.c fight.c

clean :
	rm -f game
