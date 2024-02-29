#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "parse.h"

char **parse(char *line,const char *delimiter){

    char **array_tokens = malloc(sizeof(char *));
    int array_number_values = 0;
    int array_capacity = 1;

    // Tokenize the line using the delimiter
    char *value = strsep(&line, delimiter);
    while(value){
        // Add the value to the row
        if (array_number_values == array_capacity) {
            array_capacity *= 2;
            array_tokens = realloc(array_tokens, array_capacity * sizeof(char *));
        }
        array_tokens[array_number_values++] = strdup(value);

        // Get the next value
        value = strsep(&line, delimiter);
    }
    return array_tokens;
} 