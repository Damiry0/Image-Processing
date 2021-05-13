all:myapp

myapp: odczyt1.o konturowanie.o czytaj.o progowanie.o 
	gcc -Wall -o myapp odczyt1.o konturowanie.o czytaj.o progowanie.o 
odczyt1.o: odczyt1.c
	gcc -c -Wall odczyt1.c
konturowanie.o: konturowanie.c
	gcc -c -Wall konturowanie.c
czytaj.o: czytaj.c
	gcc -c -Wall czytaj.c
progowanie.o: progowanie.c
	gcc -c -Wall progowanie.c
clean:
	rm odczyt1.o  
	rm konturowanie.o 
	rm czytaj.o 
	rm progowanie.o 