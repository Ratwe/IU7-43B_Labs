#ifndef __NODE__H__
#define __NODE__H__

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

#endif
