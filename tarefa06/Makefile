CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: sala_de_espera

sala_de_espera: sala_de_espera.c
	gcc $(CFLAGS) -c pessoa.c $(LDFLAGS)
	gcc $(CFLAGS) -c fila.c $(LDFLAGS)
	gcc $(CFLAGS) sala_de_espera.c -o sala_de_espera pessoa.o fila.o $(LDFLAGS)

clean:
	rm -f sala_de_espera
