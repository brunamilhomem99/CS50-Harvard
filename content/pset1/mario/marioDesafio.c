#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // input do usuário: solicitação para que o user escolha a altura da piramide
     int numeroDeColunas;

     // do-while: exibe uma condição, enquanto o input for válido (de 1 a 8) será impresso o output normalmente
     do {
    numeroDeColunas = get_int("Altura da piramide (1 a 8): ");
    if (numeroDeColunas < 1 || numeroDeColunas > 8) {
        printf("Seu input é inválido\n");
    }
} while( numeroDeColunas < 1 || numeroDeColunas > 8 );

     for( int line = 1; line <= numeroDeColunas; line++) {
         int spaces = numeroDeColunas - line;

         for( int coluna = 0; coluna < spaces; coluna++) {
             printf(" ");
         }

         int numeroDeHashes = line;
         for( int spaceHash = 0; spaceHash < numeroDeHashes; spaceHash++) {
             printf("#");
         }

        printf("  "); // espaço vazio para separar as piramides
        for( int spaceHash = 0; spaceHash < numeroDeHashes; spaceHash++) {
             printf("#");
        }
         printf("\n");
}
}