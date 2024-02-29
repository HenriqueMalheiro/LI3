#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>


int idade (int birth_date_number);

int data_number (char *data);

FILE* cria_documento(int n);

//qsort helper
int sort_Drivers_array(const void *x, const void *y);
int sort_Users_array(const void *x, const void *y);
int sort_Statistics_Q5_6(const void *x, const void *y);
int sort_arrayDriversCity_Q7(const void *x, const void *y);
int sort_Statistics_Q8(const void *x, const void *y);
int sort_Statistics_Q9(const void *x, const void *y);
int number_lines();
#endif