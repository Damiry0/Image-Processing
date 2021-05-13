#include "czytaj.h"
#include "struct.h"
#include "konturowanie.h"
#include "progowanie.h"

int odczytano = 0;
char nazwa[100];
char wynik[100];

/*******************************************************/
/* Funckja wczytująca zawartosc wybranego pliku do     */
/* dynamicznie alokowanej tablicy                      */
/*                                                     */
/* Parametry:                                          */
/* File *plik_we - plik wejściowy                      */
/* t_obraz *obraz - struktura danych w ktorej          */
/*                  przechowywane beda podstawowe      */
/*                  parametry obrazu                   */
/* PRE:                                                */
/*   podany zgodny z specyfikacją formatu plik ppm lub */
/*   ppm lub pgm                                       */
/* POST:                                               */
/*  poprawnie wczytane obraz wraz z jego właściwościami*/
/*  oraz poprawnie odczytano rodzaj pliku              */                 
/*                                                     */
/*******************************************************/
int czytaj(FILE *plik_we, t_obraz *obraz)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */
  int i, j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku.Nacisnij dowolny przycisk aby przejsc dalej.\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */
  if ((buf[0] == 'P' && buf[1] == '3'))
  {
    do
    {
      if ((znak = fgetc(plik_we)) == '#')
      {                                            /* Czy linia rozpoczyna sie od znaku '#'? */
        if (fgets(buf, DL_LINII, plik_we) == NULL) /* Przeczytaj ja do bufora                */
          koniec = 1;                              /* Zapamietaj ewentualny koniec danych */
      }
      else
      {
        ungetc(znak, plik_we);        /* Gdy przeczytany znak z poczatku linii */
      }                               /* nie jest '#' zwroc go                 */
    } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
    /* i nie nastapil koniec danych         */
    fscanf(plik_we, "%d", &(obraz->wymx));
    fscanf(plik_we, "%d", &(obraz->wymy));
    fscanf(plik_we, "%d", &(obraz->szarosci));
    obraz->piksele = malloc(3 * obraz->wymx * obraz->wymy * sizeof(int)); // potrzebujemy 3 razy wiekszej pamieci bo jeden pixel obrazu sklada sie teraz z 3 liczb
    int(*piksele)[obraz->wymx];
    piksele = (int(*)[obraz->wymx])obraz->piksele;
    for (j = 0; j < 3 * obraz->wymy; j++)
    {
      for (i = 0; i < obraz->wymx; i++)
      {
        if (fscanf(plik_we, "%d", &(piksele[j][i])) != 1)
        {
          fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu.Nacisnij dowolny przycisk aby przejsc dalej.\n");
          getchar();
          getchar();
          return (0);
        }
      }
    }

    return 3; /* Czytanie zakonczone sukcesem, wczytano plik ppm   */
  }

  if ((buf[0] != 'P') || (buf[1] != '2') || koniec)
  { /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM ani PPM.Nacisnij dowolny przycisk aby przejsc dalej.\n");
    getchar();
    getchar();
    return (0);
  }

  /* Pominiecie komentarzy */
  do
  {
    if ((znak = fgetc(plik_we)) == '#')
    {                                            /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, plik_we) == NULL) /* Przeczytaj ja do bufora                */
        koniec = 1;                              /* Zapamietaj ewentualny koniec danych */
    }
    else
    {
      ungetc(znak, plik_we);        /* Gdy przeczytany znak z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */
  fscanf(plik_we, "%d", &(obraz->wymx));
  fscanf(plik_we, "%d", &(obraz->wymy));
  fscanf(plik_we, "%d", &(obraz->szarosci));
  obraz->piksele = malloc(obraz->wymx * obraz->wymy * sizeof(int));
  int(*piksele)[obraz->wymx];
  piksele = (int(*)[obraz->wymx])obraz->piksele;
  for (j = 0; j < obraz->wymy; j++)
  {
    for (i = 0; i < obraz->wymx; i++)
    {
      if (fscanf(plik_we, "%d", &(piksele[j][i])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu.Nacisnij dowolny przycisk aby przejsc dalej.\n");
        getchar();
        getchar();
        return (0);
      }
    }
  }

  return 2; /* Czytanie zakonczone sukcesem, wczytano plik pgm   */
}
/*******************************************************/
/* Funckja zapisująca zawartosc struktury z obrazem    */
/* do wybranego przez uzytkownika pliku                */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*  char *nazwa - nazwa pliku wejsciowego              */
/*  char *wynik - nazwa pliku wyjsciowego              */
/*  int RodzPlik - rodzaj pliku z jakim mamy do        */
/*                 czynienia                           */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku jak i podane pełne nazwy   */
/*   zarowno pliku wejsiowego i wyjsciowego            */
/*                                                     */
/* POST:                                               */
/*  poprawnie wczytane obraz wraz z jego właściwościami*/
/*  oraz poprawnie odczytano rodzaj pliku              */                 
/*                                                     */
/*******************************************************/
void zapis(t_obraz *obraz, char *nazwa, char *wynik, int RodzPlik)
{
  FILE *obrazek;
  obrazek = fopen(wynik, "w");
  if (RodzPlik == 3)
  {
    fprintf(obrazek, "P3\n%d\n%d %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
    for (int j = 0; j < 3 * obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        fprintf(obrazek, "%d", obraz->piksele[j * (obraz->wymx) + i]); // zapis nastepuje tutaj przy znajomosci "Row- and column-major order",
        // z racji z ciaglymi problemami z uzyskaniem dostepu do drugiego wymiaru tablicy zdecydowalem sie na ten sposob odczytywania danych
        fprintf(obrazek, "\n");
      }
    }
  }
  else if (RodzPlik==4) // specjalny zapis dla przetwarzania ppm do pgm, zdecydowanie zbyt dlugo nad nim siedzialem
   {
    fprintf(obrazek, "P2\n%d\n%d %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
    for (int j = 0; j < obraz->wymy; j++)
    {
      for (int i = 0; i < 3*obraz->wymx; i=i+3)
      {
        fprintf(obrazek, "%d", obraz->piksele[3*j * (obraz->wymx) + i]); 
        fprintf(obrazek, "\n");
      }
    }
  }
  else
  {
    fprintf(obrazek, "P2\n%d\n%d %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
    for (int j = 0; j < obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        fprintf(obrazek, "%d", obraz->piksele[j * (obraz->wymx) + i]);// zapis nastepuje tutaj przy znajomosci "Row- and column-major order",
        // z racji z ciaglymi problemami z uzyskaniem dostepu do drugiego wymiaru tablicy zdecydowalem sie na ten sposob odczytywania danych
        fprintf(obrazek, "\n");
      }
    }
  }

  /*for (int i = 0; i < obraz->wymy; i++)
  {
    for (int j = 0; j <obraz->wymx; j++)
    {
      fprintf(obrazek, "%d",(piksele[i][j]));
    }
  }*/

  strcpy(nazwa, wynik); // nawet jeżeli nazwa byłaby dłuższa od aktualnej to nie stanowi problemu z racji że program czyta napis do momentu napotkania 0/
  fclose(obrazek);
}
/*******************************************************/
/* Funkcja wyswietla podany przez uzytkownika uchwyt   */
/*  pliku (nie samą zaladowana do struktury tablice!)  */
/* PRE:                                                */
/*      poprawnie podana nazwa pliku                   */
/* POST:                                               */
/*    wyswietlenie wskazanego przez uzytkownika pliku  */
/*******************************************************/
int wyswietl(char *n_pliku) // funkcja zmieniona z funkcji void na int aby program nie zamykał się automatycznie po wyświetleniu obrazu
{
  char polecenie[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display "); /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);    /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie); /* wydruk kontrolny polecenia */
  system(polecenie);         /* wykonanie polecenia        */
  return 1;
}

/*******************************************************/
/* Funkcja inicjuje strukture wskazywana przez wybor   */
/* PRE:                                                */
/*      poprawnie zainicjowany argument wybor (!=NULL) */
/* POST:                                               */
/*      "wyzerowana" struktura wybor wybranych opcji   */
/*******************************************************/
void wyzeruj_opcje(w_opcje *wybor)
{
  wybor->plik_we = NULL;
  wybor->plik_wy = NULL;
  wybor->negatyw = 0;
  wybor->konturowanie = 0;
  wybor->progowanie = 0;
  wybor->wyswietlenie = 0;
  wybor->polprogowaniebieli = 0;
  wybor->polprogowanieczerni = 0;
  wybor->ppm_pgm=0;
}
/************************************************************************/
/* Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/*         program {[-i nazwa] [-o nazwa] [-p liczba] [-n] [-r] [-d]    */
/*                                    [-s] [-b liczba][-c liczba]}      */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         wybor -  struktura z informacjami o wywolanych opcjach       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                     */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;         */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                    */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                         */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/
int przetwarzaj_opcje(int argc, char **argv, w_opcje *wybor, t_obraz *obraz)
{
  int i, prog = 0;
  char *nazwa_pliku_we, *nazwa_pliku_wy;

  wyzeruj_opcje(wybor);
  wybor->plik_wy = stdout; /* na wypadek gdy nie podano opcji "-o" */

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-') /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1])
    {
    case 'i':
    { /* opcja z nazwa pliku wejsciowego */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_we = argv[i];
        if (strcmp(nazwa_pliku_we, "-") == 0) /* gdy nazwa jest "-"        */
          wybor->plik_we = stdin;             /* ustwiamy wejscie na stdin */
        else                                  /* otwieramy wskazany plik   */
          wybor->plik_we = fopen(nazwa_pliku_we, "r");
        odczytano = czytaj(wybor->plik_we, obraz);
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'o':
    { /* opcja z nazwa pliku wyjsciowego */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_wy = argv[i];
        if (strcmp(nazwa_pliku_wy, "-") == 0) /* gdy nazwa jest "-"         */
          wybor->plik_wy = stdout;            /* ustwiamy wyjscie na stdout */
        else                                  /* otwieramy wskazany plik    */
          wybor->plik_wy = fopen(nazwa_pliku_wy, "w");
        zapis(obraz, nazwa_pliku_we, nazwa_pliku_wy, odczytano);
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'p':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          wybor->progowanie = 1;
          wybor->w_progu = prog;
          if (prog > 0 && prog < 100) // prog nie moze byc wiekszy od podanych wartosci precentowych
          {
            Progowanie(obraz, prog, odczytano);
          }
          else
          {
            return B_BRAKWARTOSCI; // blad: niepoprawna wartosc progu
          }
          
        }
        else
          return B_BRAKWARTOSCI; /* blad: niepoprawna wartosc progu */
      }
      else
        return B_BRAKWARTOSCI; /* blad: brak wartosci progu */
      break;
    }
    case 'n':
    { /* mamy wykonac negatyw */
      wybor->negatyw = 1;
      Negatyw(obraz, odczytano);
      break;
    }
    case 'k':
    { /* mamy wykonac konturowanie */
      wybor->konturowanie = 1;
      konturowanie(obraz,odczytano);
      break;
    }
    case 'd':
    { /* mamy wyswietlic obraz */
      wybor->wyswietlenie = 1;
      wyswietl(nazwa_pliku_we);

      break;
    }
    case 's':
    { /* mamy zamieniic obraz ppm do pgm */
      wybor->ppm_pgm = 1;
      if (odczytano==3)
      {
      odczytano=ppm_pgm(obraz,odczytano);}
      else 
      {
        return B_NIEPOPRAWNAOPCJA; 
      }
      
      break;
    }
    case 'b':
    { /* mamy polprogowac obraz w czerni */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          wybor->polprogowanieczerni = 1;
          wybor->w_progu = prog;
          
          if (prog > 0 && prog < 100)
          {
            PolProgowanieCzerni(obraz, prog, odczytano);
          }
          else
          {
            return B_BRAKWARTOSCI; // blad: niepoprawna wartosc progu
          }
        }
        else
          return B_BRAKWARTOSCI; /* blad: niepoprawna wartosc progu */
      }
      else
        return B_BRAKWARTOSCI; /* blad: brak wartosci progu */
      break;
    }
    case 'c':
    {
      // mamy polprogowac obraz w bieli
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          wybor->polprogowaniebieli = 1;
          wybor->w_progu = prog;
          if (prog > 0 && prog < 100)
          {
            PolProgowanieBieli(obraz, prog, odczytano);
          }
          else
          {
            return B_BRAKWARTOSCI; // blad: niepoprawna wartosc progu
          }
        }
        else
          return B_BRAKWARTOSCI; /* blad: niepoprawna wartosc progu */
      }
      else
        return B_BRAKWARTOSCI; /* blad: brak wartosci progu */
      break;
    }
    default: /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } 
    
  }   
  
  if (wybor->plik_we != NULL) /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else
    return B_BRAKPLIKU; /* blad:  nie otwarto pliku wejsciowego  */
}
