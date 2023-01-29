#ifndef __HASH_H__
#define __HASH_H__

#include "../inc/defines.h"

typedef struct hash_node
{
    char word[MAX_STR_LEN + 1];
    struct hash_node *next;
} hash_node_t;

typedef struct htable_opened
{
    hash_node_t **data;
    int *keys;
    size_t size;
    size_t max_size;
} htable_opened_t;

typedef struct htable_closed
{
    char **data;
    int *keys;
    size_t size;
    size_t max_size;
} htable_closed_t;

#define COLOR_WORD(x, y) (!strncmp(x, y, 1)) ? "\033[33m" : ""

void set_hash_compares(size_t compares);
size_t get_hash_compares(void);

size_t fget_len(char *fname);

void free_htable_opened(htable_opened_t *htable);
int htable_opened_find_node(htable_opened_t *htable, char *str);
int htable_opened_insert(htable_opened_t *htable, char *str);
htable_opened_t *new_hash_table_opened(size_t max_size);
int fill_htable_opened(htable_opened_t *htable, FILE **file);
int htable_opened_pop(htable_opened_t *htable, char *str);
void search_hash_opened_word(htable_opened_t *htable, char *str);
void print_htable_opened(htable_opened_t *htable);
void print_htable_opened_color(htable_opened_t *htable, char *str);
size_t get_htable_opened_size_in_bytes(htable_opened_t *htable);

void free_htable_closed(htable_closed_t *htable);
int htable_closed_find_node(htable_closed_t *htable, char *str);
int htable_closed_insert(htable_closed_t *htable, char *str);
htable_closed_t *new_hash_table_closed(size_t max_size);
int fill_htable_closed(htable_closed_t *htable, FILE **file);
int htable_closed_pop(htable_closed_t *htable, char *str);
void search_hash_closed_word(htable_closed_t *htable, char *str);
void print_htable_closed(htable_closed_t *htable);
void print_htable_closed_color(htable_closed_t *htable, char *str);
size_t get_htable_closed_size_in_bytes(htable_closed_t *htable);

#endif // __HASH_H__
