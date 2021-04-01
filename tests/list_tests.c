#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>
#include <lcthw/dbg.h>

static List *list = NULL;
static List *list_copy = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *test4 = "test4 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *copy_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");
    
    list_copy = List_create();
    mu_assert(list_copy != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_destroy(list); 
    
    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");
    // middle pop is tested in test_remove() 
    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong lat after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_insert_after()
{
    mu_assert(List_count(list) >= 2, \
            "List needs >=2 values for test_insert_after()");
    
    int _count = List_count(list);

    List_insert_after(list, list->first, test4);
    mu_assert(list->first->next->value == test4,\
            "Wrong value on insert");
    mu_assert(List_count(list) == (_count + 1),\
            "Wrong count on insert");


    // This is not test related... 
    // Do I have cleanup? Should it be part of the specific test
    char *val = List_remove(list, list->first->next);
    
    mu_assert(val == test4, \
            "Error removing insert_after test value");

    return NULL;
}

char *copy_list()
{
    /*
    Input situations:
    List (0 nodes) -> 
    List (1 node) -> 
    List (2+ nodes) -> Only test for this condition.
    */
     
    mu_assert(List_count(list) >= 2, \
            "List needs >=2 values for test_copy()");
    mu_assert(list_copy != NULL, "Must create list_copy");

    //int _count = List_count(list);

    //List_copy(list, list_copy);
    
    //Compare List params
    mu_assert(list->count == list_copy->count, "Incorrect count after list_copy().");
    mu_assert(list->first == list_copy->first, "Incorrect first value after list_copy().");
    mu_assert(list->last == list_copy->last, "Incorrect last value after list_copy().");

    //Compare ListNode values
    LIST_FORBOTH(list, first, next, cur1, list_copy, cur2){
        // Compare the node values of list and list_copy. 
        mu_assert(cur1->value == cur2->value, "Incorrect node value");           
    }


    
    return NULL;
}
    


char *all_tests()
{
    mu_suite_start();
   
    // Short Tests
    mu_run_test(test_create); // Creates List
    mu_run_test(test_push_pop); // Adds, then removes 3 values
    mu_run_test(test_unshift); // Adds 3 values
    mu_run_test(test_insert_after); // Insert after first and remove it
    mu_run_test(test_remove); // Removes & checks middle value
    mu_run_test(test_shift); // Removes & checks last 2 values
    mu_run_test(test_destroy); // Free List from memory 

    // Test Copy
    mu_run_test(copy_create);
    mu_run_test(test_unshift); // Adds 3 values
    //mu_run_test(copy_list); 

    
   

    return NULL;
}

RUN_TESTS(all_tests);


