#include <stdio.h>
#include <lcthw/dbg.h>
#include <lcthw/diy_radix.h>
#include <lcthw/array_algos.h>


void print_array_msg(int *arr, int count, int place, char *msg)
{
    printf("%s\n", msg); 
    
    int i = 0;
    int div = place/10;

    for (i = 0; i < count; i++){
        printf("raw: %d, ones: %d\n", arr[i], arr[i]%place/div);
    }
}

int place_sort(int *arr, int count, int place, compare_ab cmp)
{
    int i = 0;
    int j = 0;
    int temp = 0;
    int div = place/10;

    for (i = 0; i < count; i++){
        for (j = 0; j < count - 1; j++){
            if(cmp(arr[j]%place/div, arr[j+1]%place/div) > 0){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

    return 0;
}
