#ifndef lcthw_Array_algos_h
#define lcthw_Array_algos_h


typedef int (*compare_cb) (int a, int b);


int *Array_bubble_sort(int *numbers, int count, compare_cb cmp);


int sorted_order(int a, int b)
{
    return a - b;
}




#endif
