#include "progowanie.h"
#include "struct.h"

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