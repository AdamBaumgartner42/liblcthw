#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    void *value; 
} ListNode;

typedef struct List { 
    int count; 
    ListNode *first;
    ListNode *last;
} List;

List *List_create();
void List_destroy(List * list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL) 

void List_push(List * list, void *value);
void *List_pop(List * list);

void List_unshift(List * list, void *value);
void *List_shift(List * list);

void *List_remove(List * list, ListNode *node);
void List_insert_after(List * list, ListNode *node, void *value);
void print_List(List * list);
void List_copy(List * list, List * list_copy);
void List_join(List *listA, List *listB, List *target); 
void List_half_split(List *target, List *listA, List *listB);
void List_reverse(List *init, List *reverse);

#define LIST_FOREACH(L, S, M, V)\
ListNode *_node = NULL;\
ListNode *V = NULL;\
for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#define LIST_FORNEXT(L, S, M, V)\
_node = NULL;\
V = NULL;\
for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#define LIST_FORBOTH(L1,S,M,V1,L2,V2)\
ListNode *_node1 = NULL;\
ListNode *_node2 = NULL;\
ListNode *V1 = NULL;\
ListNode *V2 = NULL;\
for(V1 = _node1 = L1->S, V2 = _node2 = L2->S;\
    _node1 != NULL || _node2 != NULL;\
    V1 = _node1 = _node1->M , V2 = _node2 = _node2->M)


#endif


