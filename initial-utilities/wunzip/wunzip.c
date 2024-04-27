#include <stdio.h>
#include <stdlib.h>

#define ATOM_SIZE sizeof(uint32_t) + sizeof(char)

void write_uncompressed(void* atom)
{
    uint32_t count = *(uint32_t*)atom;
    char c = *(char*)(atom + sizeof(uint32_t));

    for (uint32_t i=0; i<count; ++i)
    {
        fputc(c, stdout);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    void* buf = malloc(ATOM_SIZE);

    for (int i=1; i<argc; ++i)
    {
        char* filename = argv[i];
        FILE* fptr = fopen(filename, "r");
        if (!fptr)
        {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        while (fread(buf, ATOM_SIZE, 1, fptr) != 0)
        {
            write_uncompressed(buf);
        }

        fclose(fptr);
    }

    free(buf);
    return 0;
}