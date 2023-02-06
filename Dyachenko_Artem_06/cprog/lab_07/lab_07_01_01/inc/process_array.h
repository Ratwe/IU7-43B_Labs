#ifndef __PROCESS_ARRAY__H__
#define __PROCESS_ARRAY__H__

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int funccmp(const void *a, const void *b);

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void*, const void*));

#endif
