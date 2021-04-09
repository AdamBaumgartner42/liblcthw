#include "minunit.h"
#include <lcthw/array_algos.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <string.h>

// test values
int sorted_array[] = { 1, 2, 3, 4, 5, 6};
int random_array[] = { 3, 7, 5, 8, 1, 4};

int count = sizeof(sorted_array)/sizeof(int);

int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b-a;
}
    
char *test_bubble_sort()
{
    int *rc = NULL; 
    rc = random_array;
    printf("Original array: ");
    print_array(rc);
    mu_assert(rc != NULL, "Error printing baseline array"); 
    
    rc = NULL; // reset
    rc = Array_bubble_sort(random_array, count, sorted_order);
    printf("Sorted array: ");
    print_array(rc);    
    mu_assert(rc != NULL, "Error with sorted_order"); 
    
    rc = NULL; // reset
    rc = Array_bubble_sort(random_array, count, reverse_order);
    printf("Reversed array: ");
    print_array(rc);    
    mu_assert(rc != NULL, "Error with reverse_order"); 

    return NULL;
}

void print_array(int *array)
{
    for(int i = 0; i < count; i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
}

char *all_tests()
{
    mu_suite_start();
    mu_run_test(test_bubble_sort);

    return NULL;
}

RUN_TESTS(all_tests);


