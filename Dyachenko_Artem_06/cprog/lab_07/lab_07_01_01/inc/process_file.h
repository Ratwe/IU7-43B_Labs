#ifndef __PROCESS_FILE__H__
#define __PROCESS_FILE__H__

int check_open_file(char *filename);

int calc_count(char *filename, int *count);

int fill_array(char *filename, int **arr, int count);

int write_file(char *filename, int *pb_dst, int *pe_dst);

#endif
