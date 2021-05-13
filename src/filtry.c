#include "../inc/struct.h"

/*******************************************************/
/* Funckja przetwarzania obrazu wykonujaca operacje    */
/* konturowania obrazu zgodnie z wzorem:               */
/*  G(x,y) =                                           */
/*  |L(x+ 1,y)−L(x,y)|+|L(x,y+ 1)−L(x,y)|, gdzie       */
/*  G - pixel przetworzonego obrazu                    */
/*  L - pixel obrazu wejsciowego                       */
/*  | *wyrażenie* | - wartosc bezwzgledna              */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*                   informacje na temat obrazu        */
/*  int odczytano - rodzaj pliku z jakim mamy do       */
/*                   czynienia                         */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku                            */
/* POST:                                               */
/*  poprawnie przetworzony obraz                       */
/*******************************************************/
void konturowanie(t_obraz *obraz, int odczytano)
{
  if (odczytano == 3)
  {
    for (int j = 0; j < 3 * obraz->wymx; j++)
    {
      for (int i = 0; i < obraz->wymy; i++)
      {
        obraz->piksele[j * (obraz->wymy) + i] = (abs(obraz->piksele[(j + 1) * (obraz->wymy) + i] - obraz->piksele[j * (obraz->wymy) + i])) + (abs(obraz->piksele[j * (obraz->wymy) + i + 1] - obraz->piksele[j * (obraz->wymy) + i]));
      }
    }
  }
  else
  {
    for (int i = 0; i < obraz->wymx; i++)
    {
      for (int j = 0; j < obraz->wymy; j++)
      {
        obraz->piksele[j * (obraz->wymx) + i] = (abs(obraz->piksele[(j + 1) * (obraz->wymx) + i] - obraz->piksele[j * (obraz->wymx) + i])) + (abs(obraz->piksele[j * (obraz->wymx) + i + 1] - obraz->piksele[j * (obraz->wymx) + i]));
      }
    }
  }
}

int ppm_pgm(t_obraz *obraz, int odczytano)
{
  for (int j = 0; j < obraz->wymy; j++)
  {
    for (int i = 0; i < 3 * obraz->wymx; i = (i + 3))
    {
      obraz->piksele[(3 * j * (obraz->wymx) + i)] = (obraz->piksele[(3 * j * (obraz->wymx) + i)] + obraz->piksele[(3 * j * (obraz->wymx) + i + 1)] + obraz->piksele[3 * j * (obraz->wymx) + i + 2]) / 3;
    }
  }

  odczytano = 4; // zmiana traktowania pliku z ppm do pgm, 2=pgm 3=ppm
  return odczytano;
}

/*******************************************************/
/* Funckja przetwarzania obrazu wykonujaca operacje    */
/* negatywu obrazu zgodnie z wzorem:                   */
/*  G(x,y) = MAX−L(x,y), gdzie                         */
/*  G - pixel przetworzonego obrazu                    */
/*  L - pixel obrazu wejsciowego                       */
/*  MAX - maksymalna stala szarosci/nasycenia w pliku  */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*                   informacje na temat obrazu        */
/*  int odczytano - rodzaj pliku z jakim mamy do       */
/*                   czynienia                         */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku                            */
/* POST:                                               */
/*  poprawnie przetworzony obraz                       */
/*******************************************************/
void Negatyw(t_obraz *obraz, int odczytano)
{
  if (odczytano == 3)
  {
    for (int i = 0; i < obraz->wymx; i++)
    {
      for (int j = 0; j < 3 * obraz->wymy; j++)
      {
        obraz->piksele[j * (obraz->wymx) + i] = abs(obraz->szarosci - obraz->piksele[j * (obraz->wymx) + i]); // bez wartosci bezwglednej przy kombinacji konturowanie->negacja wychodza wartosci ujemne ktore psują obrazek
      }
    }
  }
  else
  {
    for (int i = 0; i < obraz->wymx; i++)
    {
      for (int j = 0; j < obraz->wymy; j++)
      {
        obraz->piksele[j * (obraz->wymx) + i] = abs(obraz->szarosci - obraz->piksele[j * (obraz->wymx) + i]); // bez wartosci bezwglednej przy kombinacji konturowanie->negacja wychodza wartosci ujemne ktore psują obrazek
      }
    }
  }
}



/*******************************************************/
/* Funckja przetwarzania obrazu wykonujaca operacje    */
/* progowania obrazu zgodnie z wzorem                  */
/*  G(x,y) ={                                          */
/*  0   dla L(x,y)<=PROG                               */     
/*  MAX dla L(x,y)> PROG  gdzie:                       */
/*  G - pixel przetworzonego obrazu                    */
/*  L - pixel obrazu wejsciowego                       */
/*  PROG - wartosc progowania podana przez uzytkownika */
/*  MAX - maksymalna stala szarosci/nasycenia w pliku  */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*                   informacje na temat obrazu        */
/*  int prog - wartosc progowania                      */
/*  int odczytano - rodzah pliku z jakim mamy do       */
/*                   czynienia                         */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku jak i wartosc progu z      */
/*   przedzialu od 0 do 100                            */
/*                                                     */
/*                                                     */
/* POST:                                               */
/*  poprawnie przetworzony obraz                       */ 
/*******************************************************/
void Progowanie(t_obraz *obraz, int prog, int odczytano)
{
  int mpk = (obraz->szarosci * prog) / 100; // z racji że oprerujemy na samych intach będą one automatycznie zaokrąglały nie wywołując komplikacji w programie
  if (odczytano == 3)
  {
    for (int j = 0; j < 3 * obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] <= mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = 0;
        }
        else
        {
          obraz->piksele[j * (obraz->wymx) + i] = obraz->szarosci;
        }
      }
    }
  }
  else
  {
    for (int j = 0; j <  obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] <= mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = 0;
        }
        else
        {
          obraz->piksele[j * (obraz->wymx) + i] = obraz->szarosci;
        }
      }
    }
  }
}

/*******************************************************/
/* Funckja przetwarzania obrazu wykonujaca operacje    */
/* progowania czerni obrazu zgodnie z wzorem           */
/*  G(x,y) ={                                          */
/*  0      dla L(x,y)<=PROG                            */     
/*  L(x,y) dla L(x,y)> PROG  gdzie:                    */
/*  G - pixel przetworzonego obrazu                    */
/*  L - pixel obrazu wejsciowego                       */
/*  PROG - wartosc progowania podana przez uzytkownika */
/*  MAX - maksymalna stala szarosci/nasycenia w pliku  */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*                   informacje na temat obrazu        */
/*  int prog - wartosc progowania                      */
/*  int odczytano - rodzah pliku z jakim mamy do       */
/*                   czynienia                         */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku jak i wartosc progu z      */
/*   przedzialu od 0 do 100                            */
/*                                                     */
/*                                                     */
/* POST:                                               */
/*  poprawnie przetworzony obraz                       */ 
/*******************************************************/
void PolProgowanieCzerni(t_obraz *obraz, int prog, int odczytano)
{
  int mpk = (obraz->szarosci * prog) / 100;
  if (odczytano == 3)
  {
    for (int j = 0; j < 3 * obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] <= mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = 0;
        }
      }
    }
  }
  else
  {
    for (int j = 0; j <  obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] <= mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = 0;
        }
      }
    }
  }
}
/*******************************************************/
/* Funckja przetwarzania obrazu wykonujaca operacje    */
/* progowania bieli obrazu zgodnie z wzorem            */
/*  G(x,y) ={                                          */
/*  L(x,y) dla L(x,y)<=PROG                            */     
/*  MAX    dla L(x,y)> PROG  gdzie:                    */
/*  G - pixel przetworzonego obrazu                    */
/*  L - pixel obrazu wejsciowego                       */
/*  PROG - wartosc progowania podana przez uzytkownika */
/*  MAX - maksymalna stala szarosci/nasycenia w pliku  */
/*                                                     */
/* Parametry:                                          */
/*  t_obraz *obraz - struktura danych w ktorej         */
/*                   przechowywane sa podstawowe       */
/*                   informacje na temat obrazu        */
/*  int prog - wartosc progowania                      */
/*  int odczytano - rodzah pliku z jakim mamy do       */
/*                   czynienia                         */
/* PRE:                                                */
/*   poprawnie wczytany do struktury obraz             */
/*   wraz z jego właściwościami oraz poprawnie         */
/*   odczytany rodzaj pliku jak i wartosc progu z      */
/*   przedzialu od 0 do 100                            */
/*                                                     */
/*                                                     */
/* POST:                                               */
/*  poprawnie przetworzony obraz                       */ 
/*******************************************************/
void PolProgowanieBieli(t_obraz *obraz, int prog, int odczytano)
{
  int mpk = (obraz->szarosci * prog) / 100;
  if (odczytano == 3)
  {
    for (int j = 0; j < 3 * obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] > mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = obraz->szarosci;
        }
      }
    }
  }
  else
  {
    for (int j = 0; j <  obraz->wymy; j++)
    {
      for (int i = 0; i < obraz->wymx; i++)
      {
        if (obraz->piksele[j * (obraz->wymx) + i] > mpk)
        {
          obraz->piksele[j * (obraz->wymx) + i] = obraz->szarosci;
        }
      }
    }
  }
}
