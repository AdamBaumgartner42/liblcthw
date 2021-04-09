#include "minunit.h"
#include <lcthw/array_algos.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <string.h>

// test values
int sorted_array[] = { 1, 2, 3, 4, 5, 6};
int random_array[] = { 3, 7, 5, 8, 1, 4};

char *test_bubble_sort()
{
    //int count = sizeof(sorted_array)/sizeof(int);
    //int *rc = Array_bubble_sort(random_array, count, (compare_cb) sorted_order);


    return NULL;
}


char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);

    return NULL;
}

RUN_TESTS(all_tests);


