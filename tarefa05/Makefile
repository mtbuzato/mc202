CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: calculadora

calculadora: calculadora.c
	gcc $(CFLAGS) -c bignum.c $(LDFLAGS)
	gcc $(CFLAGS) -c bignumops.c $(LDFLAGS)
	gcc $(CFLAGS) calculadora.c -o calculadora bignum.o bignumops.o $(LDFLAGS)

clean:
	rm -f calculadora
