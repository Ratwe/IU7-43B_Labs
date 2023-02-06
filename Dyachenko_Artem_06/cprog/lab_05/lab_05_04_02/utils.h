#ifndef __UTILS__H__
#define __UTILS__H__

int get_size(FILE *f, int *size);

int put_product_by_pos(FILE *f, product_t product, int pos);

int get_product_by_pos(FILE *f, int pos, product_t *product);

int copy_file(FILE *f_src, FILE *f_dest);

#endif
