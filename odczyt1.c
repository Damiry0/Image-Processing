// Damian Ryś 26.12.2019 nr indeksu 252936 mama nie byla zła za programowanie w swieta
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "konturowanie.h"
#include "czytaj.h"
#include "progowanie.h"
#include "struct.h"

#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4


int czytaj(FILE *plik_we, t_obraz *obraz);
int wyswietl(char *n_pliku); // funkcja zmieniona z funkcji void na int aby program nie zamykał się automatycznie po wyświetleniu obrazu
void zapis(t_obraz *obraz, char *nazwa, char *wynik, int RodzPlik); // zamien Odczytano na rodzaj pliku
void konturowanie(t_obraz *obraz,int odczytano);  // odczytano- przechowuje informacje o tym jakim typem plikow mamy do czynienia
void Negatyw(t_obraz *obraz,int odczytano);
void Progowanie(t_obraz *obraz, int prog,int odczytano);
void PolProgowanieCzerni(t_obraz *obraz, int prog,int odczytano);
void PolProgowanieBieli(t_obraz *obraz, int prog,int odczytano);
int ppm_pgm(t_obraz *obraz,int odczytano); // funckja przeksztalcajaca obraz ppm do pgm
int przetarzaj_opcje(int argc, char **argv, w_opcje *wybor,t_obraz *t_obraz); 

int main(int argc, char ** argv)
{
  t_obraz obraz;
  w_opcje opcje;
  printf("%d\n", przetwarzaj_opcje(argc,argv,&opcje,&obraz)); 

/*******************************************************/
/*                  Sprawozdanie                       */
/*******************************************************/
/* Początkowym testem było przetestowanie na przykładzie obrazka kubus.pgm wszystkich funkcji aby sprawdzić poprawność nowo zaimplementowanych struktur danych z plikiem z przetwarzaniem obrazow 1.
Wszystkie funkcje zwracaja dokladni tak samo przeksztalcony obraz uznaje zatem ze nowo struktury przechowujace dane jak i samo dynamiczne alokowanie pamieci dziala poprawnie dla obrazow pgm.
Nastepnym testem było przetestowanie na przykladzie obrazka Lena.ppm kolejni wszystkich funkcji programu aby sprawdzic poprawnosc samych funkcji jak i nowej struktury dla plikow ppm. 
Funkcja negatywu jak i trzy funkcje progowania dzialaja bez zarzutu co wskazuje na prawidlowa implementacje struktury wraz z przekazywaniem danych. Natomiast funkcje konturowania nie spelniaja swoich funkcji.
Konturowanie mimo uzycia prawidlowego wzoru jak i proby zaimplementowania wzorow dostepnych na archiwalnych wersjach Pana strony nie przyniosly oczekiwanego skutku 
( czyli takiego jaki mozna uzyskac po uzyciu funkcji: convert -convolve 0,0,0,0,-2,1,0,1,0 plik.ppm plik.ppm w terminalu). 
Poprawnie za to dziala funkcja konwertowanie obrazow ppm do pgm nad ktora stracilem zdecydowanie za duzo czasu poszukujac bledu co bylo jednym z glownych powodow nie oddania pracy w terminie za co przepraszam. 
W dalszej czesci testow sprawdzana byla obsluga podstawowych bledow tzn. niepoprawnie wybranej opcji, braku nazwy pliku, braku wartosci czy braku pliku. Program poprawnie sygnalizuje niepodanie '-' przed argumentem, 
braku nazwy pliku zarowno po "-o" jak i "-i", braku podania wartosci progowania po "-p","-a","-b" oraz prawidlowo sygnalizuje braku dostepnosci takiego pliku. Moge zatem uznac ze ta czesc programu dziala prawidlowo         */
/****************************************************************/
/*                    Wnioski                                   */
/****************************************************************/
/*  Program przeszedł pomyślnie (prawie) każdy postawiony przez */
/*  niego test i przetestowana została każda część              */
/*  algorytmu.Biorąc pod uwagę powyższe wyniki można            */
/*  uznać, że program działa (prawie) poprawnie                 */                 
/*                                                              */
/****************************************************************/
}
