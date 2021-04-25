#ifndef diy_radix_h
#define diy_radix_h


typedef int (*compare_ab) (int a, int b);

int place_sort(int *arr, int count, int place, compare_ab cmp);

void print_array_msg(int *arr, int count, int place, char *msg);




#endif
