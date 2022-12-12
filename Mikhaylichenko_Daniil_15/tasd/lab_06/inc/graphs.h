#ifndef __GRAPHS_H__
#define __GRAPHS_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../inc/defines.h"
#include "../inc/tree.h"

int tree_to_dot(tree_node_t *tree, char *dot_name);
int dot_to_svg(char *dot_name, char *svg_name);
int open_svg(char *svg_name);

#endif // __GRAPHS_H__
