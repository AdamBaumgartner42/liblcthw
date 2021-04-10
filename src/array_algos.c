#include <lcthw/array_algos.h>
#include <lcthw/dbg.h>
#include <stdlib.h>

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int *Array_bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    memcpy(target, numbers, count * sizeof(int));

    for (i = 0; i < count; i++) {
        for (j = 0; j < count - 1; j++) { 
            if(cmp(target[j], target[j + 1]) > 0) {
                temp = target[j + 1];
                target[j + 1] = target[j];
                target[j] = temp;
            }
        }
    }
    
    return target;
}

void print_array(int *array, int count)
{
    for(int i = 0; i < count; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
}

