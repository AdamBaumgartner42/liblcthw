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

void List_clear(List * list)
{
    LIST_FOREACH(list, first, next, cur) { 
        free(cur->value);
    }
}

void List_clear_destroy_combo(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev){
            free(cur->prev->value);
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);
}


void List_clear_destroy(List * list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List * list, void *value)
{
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
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List * list, void *value)
{
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
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void *result = NULL;

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


