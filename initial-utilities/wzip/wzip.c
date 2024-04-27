#include <stdio.h>
#include <stdlib.h>

#define READ_BUF_SIZE_CHARS 8

void write_compressed(char* cur_char, uint32_t* cur_count, char* str)
{
    // printf("Invocation: %s\n", str);
    for (size_t i=0; str[i] != '\0'; ++i)
    {
        char c = str[i];
        // printf("%c\n", c);
        if (c == *cur_char && *cur_count < UINT32_MAX)
        {
            ++(*cur_count);
        }
        else
        {
            if (*cur_count > 0)
            {
                // printf("Writing %i%c\n", *cur_count, *cur_char);
                fwrite(cur_count, sizeof(uint32_t), 1, stdout);
                fwrite(cur_char, sizeof(char), 1, stdout);
            }

            *cur_char = c;
            *cur_count = 1;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    char* buf = malloc(sizeof(char) * READ_BUF_SIZE_CHARS);
    char cur_char;
    uint32_t cur_count = 0;

    for (int i=1; i<argc; ++i)
    {
        char* filename = argv[i];
        FILE* fptr = fopen(filename, "r");
        if (!fptr)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        char* str = fgets(buf, READ_BUF_SIZE_CHARS, fptr);
        while (str)
        {
            write_compressed(&cur_char, &cur_count, str);
            str = fgets(buf, READ_BUF_SIZE_CHARS, fptr);
        }

        fclose(fptr);
    }

    if (cur_count > 0)
    {
        // printf("Writing %i%c\n", cur_count, cur_char);
        fwrite(&cur_count, sizeof(uint32_t), 1, stdout);
        fwrite(&cur_char, sizeof(char), 1, stdout);
    }

    free(buf);
    return 0;
}