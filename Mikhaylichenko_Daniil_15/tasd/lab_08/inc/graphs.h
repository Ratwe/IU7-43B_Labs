#ifndef __GRAPHS_H__
#define __GRAPHS_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../inc/defines.h"
#include "../inc/list_graph.h"
#include "../inc/matrix_graph.h"

void write_matrix_graph(FILE **file, void *graph);
void write_list_graph(FILE **file, void *graph);
int graph_to_dot(void *graph, char *dot_name, void (*write_paths)(FILE **file, void *graph));
int dot_to_svg(char *dot_name, char *svg_name);
int open_svg(char *svg_name);

#endif // __GRAPHS_H__
