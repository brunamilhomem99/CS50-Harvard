#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int array[26];
    int is_text = 0;
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
        is_text = 0;
        break;
        }

        if(!is_text)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        for (int j = 0; j < i; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }

        if (islower(argv[1][i]))
        {
            array[i] = argv[1][i] - 97;
        }
        else
        {
            array[i] = argv[1][i] - 65;
        }
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int k = array[tolower(plaintext[i]) - 'a'];

            if (islower(plaintext[i]))
            {
                printf("%c", (k % 26) + 'a');
            }
            else
            {
                printf("%c", (k % 26) + 'A');
            }
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");
    return 0;
}
