#include "minunit.h"
#include <lcthw/diy_radix.h>
#include <lcthw/array_algos.h>

// sample array

int arr[] = { 145, 357, 739, 603, 19, 1937, 581 };

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

char * test_diy_radix()
{
    int rc = 0;
    int count = sizeof(arr)/(sizeof(int));
   
    // 10s
    rc = place_sort( arr, count, 10, sorted_order);
    mu_assert(rc == 0, "Error in 10_sort()");

    // 100s
    rc = place_sort( arr, count, 100, sorted_order);
    mu_assert(rc == 0, "Error in 100_sort()");
    // 1000s
    rc = place_sort( arr, count, 1000, sorted_order);
    mu_assert(rc == 0, "Error in 1000_sort()");
    // 10000s
    rc = place_sort( arr, count, 10000, sorted_order);
    mu_assert(rc == 0, "Error in 10000_sort()");
    
    rc = is_sorted(arr, count);    
    mu_assert(rc == 1, "diy_radix array is not sorted");

    return NULL;

}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_diy_radix);

    return NULL;
}

RUN_TESTS(all_tests);
