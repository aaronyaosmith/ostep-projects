#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_file(char* query, FILE* fptr)
{
    char* line = NULL;
    size_t linecap = 0;
    ssize_t linelen = 0;

    while (linelen >= 0)
    {
        linelen = getline(&line, &linecap, fptr);
        // printf("Got line:\n\n%s\n\n", line);
        // printf("Query:\n\n%s\n\n", query);
        if (strstr(line, query))
        {
            printf("%s", line);
        }
    }

    free(line);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char* query = argv[1];

    if (argc < 3)
    {
        search_file(query, stdin);
    }

    for (int i=2; i<argc; ++i)
    {
        char* filename = argv[i];
        FILE* fptr = fopen(filename, "r");
        if (!fptr)
        {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        search_file(query, fptr);

        fclose(fptr);
    }

    return 0;
}