#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// cria constantes globais uteis e define tipos que serão usados
const int chunk_size = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // filtro de uso
    if (argc != 2)
    {
        printf("usage: ./recover<filename.raw\n");
        return 1;
    }

    // abrindo o arquivo enquanto filtra o seu uso
    // obs: é necessário fechar o arquivo quando terminar
    FILE *file = fopen(argv[1], "r"); // pointer = "FILE *"
    if (file == NULL)
    {
        printf("Empty file /Reading error\n");
        return 1;
    }

    // criando variáveis pra efetuar a leitura e modificação de dados pela função fread
    // obs: sempre que usar 'malloc' deve usar o 'free' para liberar a memória alocada
    BYTE buffer[chunk_size]; // buffer armazena os dados temporareamente
    char *recovered_jpeg_name = malloc(8);
    int jpeg_count = 0;
    FILE *recovered_file;
    int writing = 0;

    // ler em blocos de 512 bytes procurando o padrão dos primeiros bytes
    while (fread(&buffer, 1, chunk_size, file))
    {
        // condição para o final de arquivo jpeg e o inicio de outro
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[3] & 0xf0) == 0xe0)
        {
            if (writing)
            {
                fclose(recovered_file);
                writing = 0;
            }

         sprintf(recovered_jpeg_name, "%03i.jpg", jpeg_count);

         // agora que já temos o nome do arquivo devemos escrever nele
         recovered_file = fopen(recovered_jpeg_name, "w");
         writing = 1;

         fwrite(buffer, 1, chunk_size, recovered_file);

         jpeg_count++;
        }

        else
        {
            if (jpeg_count > 0)
            {
                fwrite(buffer, 1, chunk_size, recovered_file);
            }
        }
    }
    fclose(recovered_file); // fechando o último arquivo

    // a variável não será mais necessária portanto deve ser liberada
    free(recovered_jpeg_name);

    // com o fim do programa, o arquivo original não será mais necessario, sendo fechado tbm
    fclose(file);
    return 0;
}