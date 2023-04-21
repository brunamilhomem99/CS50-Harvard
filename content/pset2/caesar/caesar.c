#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv [])
{
    // O argc tem que 2, pois o primeiro espaço "./ceasar" e segundo valor tem que ser o número
    if (argc != 2 || argv[1] == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int k = 0;

    //Testar se o argv é um número
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Se a função for falsa vai retornar 0, logo a entrada não é um número.
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //transformar string em inteiro
    k = atoi(argv[1]);

    //Digitar o texto a ser criptografado
    string p = get_string("Plaintext: ");
    printf("ciphertext: ");

    //Verifica o tamanho da string
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        //Verificar se o caracter é alfabético e minúsculo
        if (isalpha(p[i]) && islower(p[i]))
        {
            p[i] = p[i] - 97;
            //algoritmo de César
            int c = (p[i] + k) % 26;
            printf("%c", c + 97);
        }
        else if (isalpha(p[i]) && isupper(p[i]))
        {
            p[i] = p[i] - 65;
            int c = (p[i] + k) % 26;
            printf("%c", c + 65);
        }
        else
        {
            printf("%c", p[i]);
        }
    }
    printf("\n");
}