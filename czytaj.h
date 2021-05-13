#ifndef NAGLOWEK_H5
#define NAGLOWEK_H5


#define MAX 512
#define DL_LINII 1024
#define W_OK 0                   /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1    /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY   -2
#define B_BRAKWARTOSCI  -3
#define B_BRAKPLIKU   -4

int czytaj();
void zapisz();
int wyswietl();
int przetwarzaj_opcje();
void wyzeruj_opcje();




#endif