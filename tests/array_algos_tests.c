#include "minunit.h"
#include <lcthw/array_algos.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <string.h>

// test values
int random_array[] = { 3, 7, 5, 8, 1, 4};

    
char *test_bubble_sort()
{
    int count = sizeof(random_array)/sizeof(int);

    int *rc = NULL; 
    rc = random_array;
    //print_array(rc, count);


    rc = NULL; // reset
    rc = Array_bubble_sort(random_array, count, (compare_cb) sorted_order);
    //print_array(rc, count);
    mu_assert(rc != NULL, "Error with sorted_order"); 
    
    //rc = NULL; // reset
    //rc = Array_bubble_sort(random_array, count, reverse_order);
    //mu_assert(rc != NULL, "Error with reverse_order"); 

    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);

    return NULL;
}

RUN_TESTS(all_tests);


