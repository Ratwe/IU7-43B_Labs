#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdio.h>
#include "defines.h"

typedef struct
{
	char name[MAX_NAME_LEN + 1];
	double weight;
	double volume;
} s_subject;

int get_string(FILE *file, char *str);
int get_double(FILE *file, double *var);
int get_structs(FILE *file, s_subject all_subjects[], size_t *size);
void sort_by_density(s_subject all_subjects[], size_t size);
int is_begining(char *sub_str, char *str);
void print_struct(s_subject subject);

#endif // __FUNCTIONS_H__