#ifndef __LIST_GRAPH_H__
#define __LIST_GRAPH_H__

#include "../inc/defines.h"
#include "../inc/array_queue.h"

typedef struct node
{
    int index;
    int path_len;
    struct node *next;
} node_t;

typedef struct list_graph
{
    node_t **nodes;
    size_t size;
} list_graph_t;

void free_list_graph(list_graph_t *graph);
int fill_list_graph(list_graph_t **graph, FILE **file);
void print_list(list_graph_t *graph);
void write_list_graph(FILE **file, void *graph);
void anti_dijkstra_list(list_graph_t *graph, int start_index);

#endif // __LIST_GRAPH_H__
