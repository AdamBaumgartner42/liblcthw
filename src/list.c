#include <lcthw/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List * list)
{
    LIST_FOREACH(list, first, next, cur) { 
        if (cur->prev){
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_push(List * list, void *value)
{
    check(list != NULL, "Invalid list."); 
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    
    node->value = value;

    if (list -> last == NULL) { // special case for brand new list (no data)
        list->first = node;  // Only 1 node (first and last = same thing)
        list->last = node;  // Only a single node (same value)
    } else {
        list->last->next = node; // add node to the end
        node->prev = list->last; // update node to have prev be previous last
        list->last = node; // update list to have last be node
    }

    list-> count++;

error:
    return;
}

void *List_pop(List * list)
{
    check(list != NULL, "Invalid list."); 
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
error:
    return NULL;
}

void List_unshift(List * list, void *value)

{
    check(list != NULL, "Invalid list.");
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);
    
    node->value = value;

    if (list->first == NULL) {
        list->first = node; 
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List * list)
{
    check(list != NULL, "Invalid list."); 
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
error:
    return NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void *result = NULL;

    check(list != NULL, "Invalid list."); 
    check(node != NULL, "Invalid node."); 
    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL, 
                "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev; 
        check(list->last != NULL, 
                "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else { 
        ListNode *after = node->next; 
        ListNode *before = node->prev; 
        // update link where node used to be 
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value; // log value for error
    free(node); 

error:
    return result;
}

void List_insert_after(List *list, ListNode *node, void *value)
{
    check(list != NULL, "Invalid List");
    check(node != NULL, "Node previous to insert is NULL");
    check(node->next != NULL, "Missing trailing node to insert before");

    ListNode *insert = calloc(1, sizeof(ListNode));
    insert->value = value;

    insert->next = node->next; 
    node->next->prev = insert;
    node->next = insert;
    insert->prev = node;

    list->count++;

error:
    return;
}


void print_List(List *list)
{
    printf("\n***print_List***\n");
    printf("List_count: %d\n", List_count(list));
    LIST_FOREACH(list, first, next, cur) { 
        printf("%p\n", cur->value);
    }
    printf("\n");
}

void List_copy(List *list , List *list_copy)
{
    
    check(list != NULL, "Invalid List");
    check(list_copy != NULL, "Invalid List");


    LIST_FOREACH(list, first, next, cur){
        List_push(list_copy, cur->value);
    }

error:
    return;
}


void List_merge(List *listA, List *listB, List *target)
{
    check(listA != NULL, "Invalid list input");
    check(listB != NULL, "Invalid list input");
    check(target != NULL, "Invalid list input");

    LIST_FOREACH(listA, first, next, cur){
        List_push(target, cur->value);
    }

    LIST_FORNEXT(listB, first, next, cur){
        List_push(target, cur->value);
    }

error:
    return;
}

void List_half_split(List *total, List *listA, List *listB)
{
    check(total != NULL, "total list must be initialized"); 
    check(listA != NULL, "listA must be initialized"); 
    check(listB != NULL, "listB list must be initialized"); 
    
    check(List_count(total) > 1, "total list must be at least 2 or more values");

    // Find half position:
    int half_mark = List_count(total)/2;
    int index = 0; 

    // Push values around the half position
    LIST_FOREACH(total, first, next, cur){
        if (index < half_mark){
            List_push(listA, cur->value);
        } else { 
            List_push(listB, cur->value);
        }
        index++;
    }

error:
    return;
}


void List_reverse(List *init, List *reverse)
{
    check(init != NULL, "init must be initialized");
    check(reverse != NULL, "reverse must be initialized");
   
    // Read out init in reverse order -> to reverse list
    LIST_FOREACH(init, last, prev, cur){ // values read in reverse order
        List_push(reverse, cur->value); // add value to reverse
    }

error:
    return;

}


