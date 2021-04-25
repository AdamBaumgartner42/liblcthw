#include "minunit.h"
#include <lcthw/diy_radix.h>


// sample array

int arr[] = { 145, 357, 739, 603, 169, 937, 581 };

char * test_diy_radix()
{
    //printf("arr: %d\n", arr[4]); 
    
    // Goal: Sort arr[] by the "ones" place numbers.
    
    // Actions: 
    // Bubble sort but only look at the first digit with "%10"
    // -> int ones_sort( int *target){
    // || rc == 0: OK, rc == -1: NG
    // >> rc = ones_sort(&arr);

    int count = sizeof(arr)/(sizeof(int));

    int rc = ones_sort( arr, count );
    
    mu_assert(rc == 0, "Error in ones_sort()");


    return NULL;

}


char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_diy_radix);

    return NULL;
}

RUN_TESTS(all_tests);
