__start__: ./myapp
		./myapp

./myapp: obj obj/odczyt1.o obj/filtry.o obj/czytaj.o  
	gcc -Wall -pedantic -o ./myapp obj/odczyt1.o obj/filtry.o obj/czytaj.o  

obj:
	mkdir -p obj

obj/odczyt1.o:  src/odczyt1.c
	gcc -c -pedantic -Wall src/odczyt1.c
obj/filtry.o: inc/filtry.h src/filtry.c
	gcc -c -pedantic -Wall src/filtry.c
obj/czytaj.o: inc/czytaj.h src/czytaj.c
	gcc -c -pedantic -Wall src/czytaj.c
clean:
	rm -f obj/*.o ./myapp