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

    for(i = 0; i < count; i++){
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
    rc = random_array;

    rc = NULL; // reset
    rc = Array_bubble_sort(random_array, count, (compare_cb) sorted_order);
    mu_assert(rc != NULL, "Error with sorted_order"); 
    mu_assert(is_sorted(rc, count),"List is not in order");
     
    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);

    return NULL;
}

RUN_TESTS(all_tests);


