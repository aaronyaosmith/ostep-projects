#include <stdio.h>
#include <stdlib.h>

#define READ_BUF_SIZE_CHARS 1024

int main(int argc, char* argv[])
{
    char* buf = malloc(sizeof(char) * READ_BUF_SIZE_CHARS);

    for (int i=1; i<argc; ++i)
    {
        char* filename = argv[i];
        FILE* fptr = fopen(filename, "r");
        if (!fptr)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        char* str = fgets(buf, READ_BUF_SIZE_CHARS, fptr);
        while (str)
        {
            printf("%s", str);
            str = fgets(buf, READ_BUF_SIZE_CHARS, fptr);
        }

        fclose(fptr);
    }

    free(buf);

    return 0;
}