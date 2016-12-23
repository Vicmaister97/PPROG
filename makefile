#-----------------------
# De momento probamos con el maravilloso c90
# Si quereis probarlo con vuestros ficheros, adelante, añadid lo que sea
#-----------------------

CC = gcc -std=c99 -pedantic
CFLAGS = -Wall -g
EXE = pruebagame

all : $(EXE)

.PHONY : clean
clean :
	rm -f *.o core $(EXE)

%.o: %.c *.h
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

$(EXE) : % : %.o cop.o space.o world.o player.o object.o myintrf.o rectangles.o game.o pruebagame.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o cop.o space.o world.o player.o object.o myintrf.o rectangles.o game.o pruebagame.o
