#include "minunit.h"
#include <lcthw/array_algos.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <string.h>

// test values
int random_array[] = { 3, 7, 5, 8, 1, 4};


int is_sorted(int *nums, int count)
{
    int i = 0; 

    for(i = 0; i < count-1; i++){
        if(nums[i] > nums [i+1]){
            printf("Error: i:%d [i]:%d, [i+1]:%d\n", i, nums[i], nums[i+1]);
            return 0; 
        }
    }
    return 1; 

}
    
char *test_bubble_sort()
{
    int count = sizeof(random_array)/sizeof(int);
    int *rc = NULL; 
    rc = Bubble_sort(random_array, count, (compare_cb) sorted_order);
    mu_assert(rc != NULL, "Error with Bubble_sort()"); 
    mu_assert(is_sorted(rc, count),"Bubble_sort() array is not in order");
     
    return NULL;
}

char *test_merge_sort()
{
    int arr[] = { 3, 7, 5, 8, 1, 4};
    int arr_size = sizeof(arr)/sizeof(int);
    
    mergeSort(arr, 0, arr_size - 1);
    
    mu_assert(is_sorted(arr, arr_size),"arr[] is not in order");
     
    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);


