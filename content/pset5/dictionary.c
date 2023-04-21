// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

#define N 26

// Number of buckets in hash table
unsigned int count_words = 0;

// Hash table
node *table[N];

// recebe uma palavra como entrada e retorna 'true'
// se a palavra estiver no dicionário, e 'false' caso contrário.
bool check(const char *word)
{
    // TODO
    // obtendo o índice (bucket) da tabela hash correspondente a palavra
    int index = hash(word);

    // transpassa a lista encadeada para a tabela hash[index]
    for (node *cursor = table[index]; cursor !=  NULL; cursor = cursor->next)
    {
        // compara cada palavra da lista com a palavra fornecida no input
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // retorna verdadeiro caso a palavra esteja no dicionário
        }
    }
    return false;// retorna falso caso contrário
}

// recebe uma palavra como entrada e retorna
// um índice na tabela hash onde essa palavra deve ser armazenada.
unsigned int hash(const char *word)
{
    // TODO
    if (islower(word[0]))
    {
        int x = word[0] - 97;
        return x;
    }
    else if (isupper(word[0]))
    {
        int x = word[0] - 65;
        return x;
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // abrir o arquivo de dicionário
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // icicializar uma tabela hash
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // ler cada palavra do arquivo e adicioná-la à tabela hash
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // alocar memória para um novo nó
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // copiar a palavra para o novo nó
        strcpy(new_node->word, word);

        // calcular o índice na tabela hash
        unsigned int index = hash(word);

        // add o novo nó à linked list correspondente
        new_node->next = table[index];
        table[index] = new_node;
    }

    // fechar o arquivo  do dicionário
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //  declarando a variável para contar as palavras
    unsigned int count = 0;

    // loop para percorrer todas as listas encadeadas da tabela hash
    for (int i = 0; i < N; i++)
    {
        for (node *n = table[i]; n != NULL; n = n->next)
        {
            // incrementa +1 ao contador de palavras para casa node
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // percorre todas as listas encadeadas na tabela hash
    // liberando a memória alocada para cada nó
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            // remember next node
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    if (cursor == NULL)
    {
        return true;
    }

    return false;
}
