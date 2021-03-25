#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_clear()
{
    List_clear(list);
    mu_assert(list->count == 0, "List_clear() fail: count != 0");
    mu_assert(list->first == NULL, "List_clear() fail: list->first != NULL.");
    mu_assert(list->last == NULL, "List_clear() fail: list->last != NULL.");
 
    return NULL;

}

char *test_destroy()
{
    List_destroy(list);
    // Need a way to test memory free. Folks use valgrind.
    // I don't know how to use valgrind in unit tests.
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


char *all_tests()
{
    mu_suite_start();
    
    mu_run_test(test_create); // Creates List
    mu_run_test(test_push_pop); // Adds, then removes 3 values
    mu_run_test(test_unshift); // Adds 3 values
    mu_run_test(test_remove); // Removes & checks middle value
    mu_run_test(test_shift); // Removes & checksi last 2 values
    mu_run_test(test_clear);
    mu_run_test(test_destroy); // without mu_assert()
   

    return NULL;
}

RUN_TESTS(all_tests);


