#include <stdio.h>
// Struktura przechowujaca obraz wraz z jego parametrami
typedef struct
{
  int wymx, wymy, szarosci; // wymiar x,y oraz współcznnik nasycenia/szarosci
  int *piksele; // wskaźnik przechowujący obraz
} t_obraz;

typedef struct {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  int negatyw,progowanie,polprogowaniebieli,polprogowanieczerni,konturowanie,wyswietlenie,ppm_pgm;      /* opcje */
  int w_progu;              /* wartosc progu dla opcji progowanie */ 
} w_opcje;