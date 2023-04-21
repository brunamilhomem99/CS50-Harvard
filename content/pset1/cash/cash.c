#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // input para o usuário colocar o valor do troco
    float troco;
    do {
        troco = get_float("Valor do troco: ");
    }
    // condição para o valor não seja negativo
    while( troco <= 0 );

    // para tranformar o número em inteiro
    int n = round(troco * 100);

    // calculando a quantidade de moedas
        int m25 = 0;
    while(n >= 25)
    {
        n = n - 25;
        m25++;
    }

        int m10 = 0;
    while(n >= 10)
    {
        n = n - 10;
        m25++;
    }

        int m5 = 0;
    while(n >= 5)
    {
        n = n - 5;
        m5++;
    }

        int m1 = 0;
    while(n >= 1)
    {
        n = n - 1;
        m1++;
    }

    // imprimir a quabtidade total de moedas
    int total = m25 + m10 + m5 + m1;
    printf("Total de moedas: %i\n", total);

}