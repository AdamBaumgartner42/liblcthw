#ifndef lcthw_array_algos_h
#define lcthw_array_algos_h

typedef int (*compare_cb) (int a, int b);

int sorted_order(int a, int b);
int *Array_bubble_sort(int *numbers, int count, compare_cb cmp);
void print_array(int *array);

#endif
