// Allocating an Array of Pointers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int a[10];
    int *b = malloc(10 * sizeof(int));

    char *c[10];
    char **d = malloc(10 * sizeof(char *));

    for (int i = 0; i < 10; i++)
    {
        d[i] = NULL;
    }

    char *some_str = "Lambda!";

    d[5] = malloc(strlen(some_str) + 1);

    strcpy(d[5], some_str);

    printf("d[5] contains \"%s\"\n", d[5]);

    for (int i = 0; i < 10; i++)
    {
        free(d[i]);
    }

    free(d);

    (void)a;
    (void)b;
    (void)c;

    return 0;
}