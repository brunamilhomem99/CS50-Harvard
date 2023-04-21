// Bibliotecas:
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>  // "isalnum e "isspace" (determina se o valor é alfanumérico ou espaço)
#include <math.h>  // função "round" (para arredondamentos)
#include <string.h>  // contagem de strings

char *input;
int main(void)
{
    input = get_string("Digite um texto para saber a calssificação indicativa escolar: ");

    int letters = 0, cont_symbols = 0, cont_spaces = 0;   // variáveias para checar a quantidade de letras
    int is_text = 1;  // variável para checar se o input do usuário são letras do alfabeto

    for(int i = 0; i < strlen(input); i++) {
        if(!isalpha(input[i])) {
            is_text = 0;
            break;
        }
    } 
    
    if(!is_text) {
        printf("O input não é um texto válido!\n");
        return 1;
    }
    
    for(int i = 0; i < strlen(input); i++) {

        if(isalnum(input[i])) {  // checagem de alfanumérico
            letters++;
        }

        if(input[i] == '.' || input[i] == '?' || input[i] == '!') {  // checagem de símbolos
            cont_symbols++;
        }


        if(isspace(input[i])) {   // checagem de espaço
            cont_spaces++;
        }
    }

    int sentences = cont_symbols;  // quantidade de símbolos = quantidade de sentenças
    int words = cont_spaces + 1;  // quantidade de palavras = quantidade de espaços = 1

    float S = (float)sentences / (float)words * 100; // cálculo de sentenças por 100 palavras
    float L = (float)letters / (float)words * 100; // cáluclo de letras por 100 palavras
    float index = 0.0588 * L - 0.296 * S - 15.8; // índice de coleman-liau

    int grade = round(index); // arrendodamento da variável

    if(grade < 1) { 
        printf("Before grade 1\n"); 
        
    }
    else if(grade > 16) { 
        printf("Grade 16+\n"); 
        
    }
    else { 
        printf("Grade %i\n", grade); }
}
