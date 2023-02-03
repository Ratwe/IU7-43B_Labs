#ifndef __MATRIX_GRAPH_H__
#define __MATRIX_GRAPH_H__

#include "../inc/defines.h"

typedef struct
{
    int **data;
    size_t size;
} matrix_graph_t;

void free_matrix_graph(matrix_graph_t *graph);
int fill_matrix_graph(matrix_graph_t **graph, FILE **file);
void print_matrix(matrix_graph_t *graph);
void write_matrix_graph(FILE **file, void *graph);
void anti_dijkstra_matrix(matrix_graph_t *graph, int start_index);

#endif // __MATRIX_GRAPH_H__
