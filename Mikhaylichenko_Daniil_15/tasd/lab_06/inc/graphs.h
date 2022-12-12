#ifndef __GRAPHS_H__
#define __GRAPHS_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../inc/defines.h"
#include "../inc/tree.h"

void write_node_no_color(FILE **file, tree_node_t *tree);
void write_node_color(FILE **file, tree_node_t *tree);
int tree_to_dot(tree_node_t *tree, char *dot_name, void (*func)(FILE **file, tree_node_t *tree));
int dot_to_svg(char *dot_name, char *svg_name);
int open_svg(char *svg_name);

#endif // __GRAPHS_H__
