#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "student.h"
#include "file_interface.h"

#define COUNT_INPUT_VALUES  1
#define CANT_OPEN_FILE      2
#define EMPTY_FILE          3

int sort_file(char *filename)
{
    int error_code = EXIT_SUCCESS;
    size_t size;
    FILE *file;
    student_t s_i, s_j, temp;

    if (!(file = fopen(filename, "rb+")))
        error_code = CANT_OPEN_FILE;
    
    if (!error_code)
    { 
        fseek(file, 0, SEEK_END);
        size = ftell(file) / sizeof(s_i);
        if (!size)
            error_code = EMPTY_FILE;
    }

    if (!error_code)
    {
        for (size_t i = 0; i < size - 1; i++)
            for (size_t j = i + 1; j < size; j++)
            {
                fseek(file, i * sizeof(s_i), SEEK_SET);
                fread(&s_i, sizeof(s_i), COUNT_INPUT_VALUES, file);
                fseek(file, j * sizeof(s_j), SEEK_SET);
                fread(&s_j, sizeof(s_j), COUNT_INPUT_VALUES, file);

                if (compare_students(&s_i, &s_j) > 0)
                {
                    fseek(file, i * sizeof(s_j), SEEK_SET);
                    fwrite(&s_j, sizeof(s_j), COUNT_INPUT_VALUES, file);
                    fseek(file, j * sizeof(s_i), SEEK_SET);
                    fwrite(&s_i, sizeof(s_i), COUNT_INPUT_VALUES, file);
                }
            }

        fseek(file, 0, SEEK_SET);
        for (size_t i = 0; i < size; i++)
        {
            fread(&temp, sizeof(temp), COUNT_INPUT_VALUES, file);
            printf("%s %s ", temp.surname, temp.name);
            
            for (size_t j = 0; j < MARK_COUNT; j++)
                printf("%d ", temp.mark[j]);

            printf("\n");
        }

        fclose(file);
    }

    return error_code;
}

int find_students_in_file(char *source_filename, char *dest_filename, char *substr)
{
    int error_code = EXIT_SUCCESS;
    size_t size;
    size_t count = 0;
    FILE *in, *out;
    student_t student;
    
    if (!(in = fopen(source_filename, "rb")))
        error_code = CANT_OPEN_FILE;

    if (!error_code && !(out = fopen(dest_filename, "wb")))
        error_code = CANT_OPEN_FILE;

    if (!error_code)
    { 
        fseek(in, 0, SEEK_END);
        size = ftell(in) / sizeof(student);
        fseek(in, 0, SEEK_SET);
        if (!size)
            error_code = EMPTY_FILE;
    }

    if (!error_code)
    {
        for (size_t i = 0; i < size; i++)
        {
            fread(&student, sizeof(student), COUNT_INPUT_VALUES, in);
            
            if (is_surname_begin(&student, substr))
            {
                fwrite(&student, sizeof(student), COUNT_INPUT_VALUES, out);
                count++;
            }
        }
        
        if (!count)
            error_code = EMPTY_FILE;

        fclose(in);
        fclose(out);
    }

    return error_code;
}

int delete_students_in_file(char *filename)
{
    int error_code = EXIT_SUCCESS;
    size_t offset = 0;
    size_t size;
    double middle = 0;
    FILE *file;
    student_t student;

    if (!(file = fopen(filename, "rb+")))
        error_code = CANT_OPEN_FILE;
    
    if (!error_code)
    { 
        fseek(file, 0, SEEK_END);
        size = ftell(file) / sizeof(student);
        fseek(file, 0, SEEK_SET);
        if (!size)
            error_code = EMPTY_FILE;
    }

    if (!error_code)
    { 
        for (size_t i = 0; i < size; i++)
        {
            fread(&student, sizeof(student), COUNT_INPUT_VALUES, file);
            
            for (size_t j = 0; j < MARK_COUNT; j++)
                middle += student.mark[j];
        }

        middle /= 1. * size;

        for (size_t i = 0; i < size; i++)
        {
            fseek(file, i * sizeof(student), SEEK_SET);
            fread(&student, sizeof(student), COUNT_INPUT_VALUES, file); 

            if (check_mark_normality(&student, middle))
            {
                fseek(file, (i - offset) * sizeof(student), SEEK_SET);
                fwrite(&student, sizeof(student), COUNT_INPUT_VALUES, file);
            }
            else
                offset++;
        }
        if (offset == size)
            error_code = EMPTY_FILE;
        
        ftruncate(fileno(file), (size - offset) * sizeof(student));
        fclose(file);
    }

    return error_code;
}
