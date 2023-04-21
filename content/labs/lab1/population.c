#include <cs50.h>
#include <stdio.h>

int main(void)
{
      // TODO: Solicite o valor inicial ao usuário
      int inicial;
      do
      {
          inicial = get_int("População inicial: ");
      }
      while (inicial < 9);

     // TODO: Solicite o valor final ao usuário
     int final;
     do
     {
         final = get_int("Populção final: ");
     }
     while (final < inicial);

     // TODO: Calcule o número de anos até o limite
     int anos = 0;
     for (anos = 0; inicial < final; anos++)
     {
         inicial = inicial + (inicial / 3) - (inicial / 4);
     }

     // TODO: Imprima o número de anos
     printf("Crescimento anual: %i anos\n", anos);

}