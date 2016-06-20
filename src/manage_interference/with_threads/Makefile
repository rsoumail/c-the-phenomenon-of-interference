all: bank_transactions

bank_transactions : fonctions.o main.o 
	cc -o bank_transactions main.o fonctions.o -pthread

main.o : main.c structures.h fonctions.h
	cc -c main.c
fonctions.o : fonctions.c fonctions.h structures.h
	cc -c fonctions.c

clean :
	rm  bank_transactions main.o fonctions.o 
