#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../inc/filtry.h"
#include "../inc/czytaj.h"
#include "../inc/struct.h"


int main(int argc, char ** argv)
{
  t_obraz obraz;
  w_opcje opcje;
  printf("%d\n", przetwarzaj_opcje(argc,argv,&opcje,&obraz)); 
}
