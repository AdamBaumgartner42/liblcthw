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

int *Bubble_sort(int *numbers, int count, compare_cb cmp)
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


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    
    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }

    /* Merge the temp arrays back into arr[1..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { 
            arr[k] = L[i];
            i++;
        } else { 
            arr[k] = R[j]; 
            j++;
        }
        k++;
    }
    
    /* Copy remaining elements of L[] */
    while (i < n1) { 
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy remaning elements of R[] */
    while (j < n2) { 
        arr[k] = R[j];
        j++;
        k++;
    }

}


void mergeSort(int arr[], int l, int r)
{
    if (l < r) { 
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


void print_array(int *array, int count)
{
    for(int i = 0; i < count; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
}

