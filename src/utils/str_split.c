#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int get_nb_words(char *str, char to_find)
{
    int count = 0;
    int no_w = 1;
    int i;

    for (i = 0; str[i] != '\0'; i += 1) {
        if (str[i] != to_find)
            no_w = 0;
        if (str[i] == to_find && !no_w) {
            count += 1;
            no_w = 1;
        }
    }
    return ((str[i - 1] != to_find) ? count + 1: count);
}

char **split_c(char *str, char separator)
{
    char del[2] = {separator, '\0'};
    int nb_words = get_nb_words(str, separator);
    int i = 0;

    char *cpy = strdup(str);

    if (!cpy) return NULL;

    char **tab = malloc(sizeof(char *) * (nb_words + 1));

    if (!tab)
        return NULL;
    tab[nb_words] = NULL;
    for (
        char *token = strtok(cpy, del);
        token != NULL;
        token = strtok(NULL, del), i++
    ) {
        tab[i] = strdup(token);
    }
    return tab;
}

void destroy_split_array(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);
}

int is_int(const char *str)
{
    char *endPtr = NULL;

    strtol(str, &endPtr, 10);

    return endPtr != str;
}

int is_float(const char *str)
{
    char *endPtr = NULL;

    strtof(str, &endPtr);

    return endPtr != str;
}