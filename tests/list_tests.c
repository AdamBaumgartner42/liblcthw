#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>
#include <lcthw/dbg.h>

static List *list = NULL;
static List *list_copy = NULL;
static List *list1 = NULL;
static List *list2 = NULL;
static List *list3 = NULL;

static ListNode *mark = NULL;

char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";
char *test4 = "test4 data";
char *test5 = "test5 data";
char *test6 = "test6 data";
char *test7 = "test7 data";
char *test8 = "test8 data";
char *test9 = "test9 data";

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
    mu_assert(List_count(list) >= 2, \
            "List needs >=2 values for test_copy()");
    mu_assert(list_copy != NULL, "Must create list_copy");

    List_copy(list, list_copy);
    
    //Compare List params
    mu_assert(list->count == list_copy->count, "Incorrect count after list_copy().");
    mu_assert(list->first->value == list_copy->first->value, "Incorrect first value after list_copy().");
    mu_assert(list->last->value == list_copy->last->value, "Incorrect last value after list_copy().");

    //Compare ListNode values
    LIST_FORBOTH(list, first, next, cur1, list_copy, cur2){
        // Compare the node values of list and list_copy. 
        mu_assert(cur1->value == cur2->value, "Incorrect node value");           
    }
    
    return NULL;
}

char *copy_destroy()
{
    List_destroy(list); 
    List_destroy(list_copy);
    
    return NULL;
}

char *merge_create()
{
    list1 = List_create();
    mu_assert(list1 != NULL, "Failed to create list.");
    
    list2 = List_create();
    mu_assert(list2 != NULL, "Failed to create list.");
    
    list3 = List_create();
    mu_assert(list3 != NULL, "Failed to create list.");

    return NULL;
}

char *merge_push_1()
{
    List_push(list1, test1);
    mu_assert(List_last(list1) == test1, "Wrong first value.");

    List_push(list1, test2);
    mu_assert(List_last(list1) == test2, "Wrong first value.");

    List_push(list1, test3);
    mu_assert(List_last(list1) == test3, "Wrong last value.");
    
    mu_assert(List_count(list1) == 3, "Wrong count on unshift.");

    return NULL;
}

char *merge_push_2()
{
    List_push(list2, test4);
    mu_assert(List_last(list2) == test4, "Wrong last value.");

    List_push(list2, test5);
    mu_assert(List_last(list2) == test5, "Wrong last value.");

    List_push(list2, test6);
    mu_assert(List_last(list2) == test6, "Wrong last value.");

    List_push(list2, test7);
    mu_assert(List_last(list2) == test7, "Wrong last value.");
    
    List_push(list2, test8);
    mu_assert(List_last(list2) == test8, "Wrong last value.");

    List_push(list2, test9);
    mu_assert(List_last(list2) == test9, "Wrong last value.");

    mu_assert(List_count(list2) == 6, "Wrong count on push.");

    return NULL;
}

char *merge_push_3()
{
    List_push(list3, test1);
    mu_assert(List_last(list3) == test1, "Wrong first value.");

    List_push(list3, test2);
    mu_assert(List_last(list3) == test2, "Wrong first value.");

    List_push(list3, test3);
    mu_assert(List_last(list3) == test3, "Wrong last value.");

    List_push(list3, test4);
    mu_assert(List_last(list3) == test4, "Wrong last value.");

    List_push(list3, test5);
    mu_assert(List_last(list3) == test5, "Wrong last value.");

    List_push(list3, test6);
    mu_assert(List_last(list3) == test6, "Wrong last value.");

    List_push(list3, test7);
    mu_assert(List_last(list3) == test7, "Wrong last value.");
    
    List_push(list3, test8);
    mu_assert(List_last(list3) == test8, "Wrong last value.");

    List_push(list3, test9);
    mu_assert(List_last(list3) == test9, "Wrong last value.");

    mu_assert(List_count(list3) == 9, "Wrong count on push.");

    return NULL;
}


char *merge_list()
{
    // *** Init check ***
    mu_assert(List_count(list1) >= 2, "Merge list must be >2");
    mu_assert(List_count(list2) >= 2, "Merge list must be >2");
    mu_assert(list3 != NULL, "Merge target must != NULL");
    
    // *** List Merge ***
    List_merge(list1, list2, list3); 

    // *** Post check ***
    // Check list3->count = list1->count + list2->count
    mu_assert(List_count(list3) == List_count(list1) + List_count(list2),\
            "Wrong list3 count on merge.");

    // Set mark to start of merged list
    mark = list3->first;
    
    // Compare merged list to values of first list
    LIST_FOREACH(list1, first, next, cur){
        //printf("list1:%s, list3:%s\n", cur->value, mark->value);
        mu_assert(cur->value == mark->value, "Merged list value error");
        mark = mark->next; // iterate list3
    }
    
    // Compare merged list to values of second list
    LIST_FORNEXT(list2, first, next, cur){
        //printf("list2:%s, list3:%s\n", cur->value, mark->value);
        mu_assert(cur->value == mark->value, "Merged list value error");
        mark = mark->next; // iterate list3
    }

    return NULL;
}

char *merge_destroy()
{
    List_destroy(list1);
    List_destroy(list2);
    List_destroy(list3);

    return NULL;
}

char *split_create()
{
    list1 = List_create();
    mu_assert(list1 != NULL, "Failed to create list.");
    
    list2 = List_create();
    mu_assert(list2 != NULL, "Failed to create list.");

    list3 = List_create();
    mu_assert(list3 != NULL, "Failed to create list.");

    return NULL;
}

char *split_push_odd()
{
    List_push(list1, test1);
    mu_assert(List_last(list1) == test1, "Wrong first value.");

    List_push(list1, test2);
    mu_assert(List_last(list1) == test2, "Wrong first value.");

    List_push(list1, test3);
    mu_assert(List_last(list1) == test3, "Wrong last value.");

    List_push(list1, test4);
    mu_assert(List_last(list1) == test4, "Wrong last value.");

    List_push(list1, test5);
    mu_assert(List_last(list1) == test5, "Wrong last value.");

    List_push(list1, test6);
    mu_assert(List_last(list1) == test6, "Wrong last value.");

    List_push(list1, test7);
    mu_assert(List_last(list1) == test7, "Wrong last value.");
    
    List_push(list1, test8);
    mu_assert(List_last(list1) == test8, "Wrong last value.");

    List_push(list1, test9);
    mu_assert(List_last(list1) == test9, "Wrong last value.");

    mu_assert(List_count(list1) == 9, "Wrong count on push.");

    return NULL;
}

char *split_push_odd_result()
{
    List_push(list2, test1);
    mu_assert(List_last(list2) == test1, "Wrong first value.");

    List_push(list2, test2);
    mu_assert(List_last(list2) == test2, "Wrong first value.");

    List_push(list2, test3);
    mu_assert(List_last(list2) == test3, "Wrong last value.");

    List_push(list2, test4);
    mu_assert(List_last(list2) == test4, "Wrong last value.");

    mu_assert(List_count(list2) == 4, "Wrong count list2"); 

    List_push(list3, test5);
    mu_assert(List_last(list3) == test5, "Wrong last value.");

    List_push(list3, test6);
    mu_assert(List_last(list3) == test6, "Wrong last value.");

    List_push(list3, test7);
    mu_assert(List_last(list3) == test7, "Wrong last value.");
    
    List_push(list3, test8);
    mu_assert(List_last(list3) == test8, "Wrong last value.");

    List_push(list3, test9);
    mu_assert(List_last(list3) == test9, "Wrong last value.");
    
    mu_assert(List_count(list3) == 5, "Wrong count list3"); 

    return NULL;
}

char *split_list_odd()
{
    // ** Pre Tests ** 
    mu_assert(List_count(list1) >= 1, "List needs more than one value to split");
   
    // ** Main Function **
    //List_split(list1, list2, list3);
    
    //** Post Test ** 
    mu_assert((List_count(list1)/2) == List_count(list2),\
            "Wrong count in first split list");
    mu_assert(List_count(list1) == List_count(list2) + List_count(list3),\
            "Wrong count in total split list count");

    // Check for values of list1 vs list2, list3
    mark = list1->first;
    
    LIST_FOREACH(list2, first, next, cur){
        mu_assert(cur->value == mark->value, "Split list2 value error");
        mark = mark->next; // iterate list3
    }
    
    LIST_FORNEXT(list3, first, next, cur){
        mu_assert(cur->value == mark->value, "Split list3 value error");
        mark = mark->next; // iterate list3
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
    mu_run_test(copy_list); 
    mu_run_test(copy_destroy);    
    
    // Test Merge
    mu_run_test(merge_create); // Creates list1, list2, list3
    mu_run_test(merge_push_1); // Adds values to list1
    mu_run_test(merge_push_2); // Adds values to list2 
    //mu_run_test(merge_push_3); // list3 (*check tests only*)
    mu_run_test(merge_list); // Merges list1 & list2 into list3
    mu_run_test(merge_destroy); // Destroys list1, list2, list3
    
    // Test Split - odd
    mu_run_test(split_create); // Creates list1, list2, list3
    mu_run_test(split_push_odd); // Adds start values to list1
    mu_run_test(split_push_odd_result); // list2, list3 (*check tests only*)
    mu_run_test(split_list_odd); // Splits list1 into list2 and list3
    //mu_run_test(split_destroy); // Destroys list1, list2, list3

    //Test Split - even
    //mu_run_test(split_create); // Creates list1, list2, list3
    //mu_run_test(split_push_even); // Adds start values to list1
    //mu_run_test(split_push_even_result); // Adds result values list2, list3
    //mu_run_test(split_list_even); // Splits list1 into list2 and list3
    //mu_run_test(split_destroy); // Destroys list1, list2, list3


    return NULL;
}

RUN_TESTS(all_tests);


