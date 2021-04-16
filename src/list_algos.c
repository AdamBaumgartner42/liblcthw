#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>


int swapListNode(List *list, ListNode *cur, ListNode *next)
{ 
    check(list->count > 1, "list->count must be > 1");
    
    // Start of list swap
    if(cur->prev == NULL){
        
        next->next->prev = cur;
        list->first = next;     
    
        next->prev = NULL; 
        cur->next = next->next;

        next->next = cur;
        cur->prev = next;
        
        return 0;
    }
    
    // End of list swap
    if(next->next == NULL){

        list->last = cur;
        cur->prev->next = next; 
    
        next->prev = cur->prev;
        cur->next = NULL;

        next->next = cur;
        cur->prev = next;
        
        return 0;
    }

    // Middle of list swap 
    next->next->prev = cur;
    
    cur->prev->next = next;
        
    next->prev = cur->prev;

    cur->next = next->next;
    
    next->next = cur;
    cur->prev = next;

    return 0;

error:
    return 1;
}

void print_cmp_log(char *s1, char *s2, int val)
{
    printf("%s, %s: %d\n",s1, s2, val);
}


int List_bubble_sort(List *words, List_compare cmp)
{
    int i = 0;
    int result = 0;

    for(i = 0; i < words->count; i++){ 
    
        LIST_FOREACH(words, first, next, cur){

            if(cur->next != NULL){
                result = cmp(cur->value, cur->next->value);
            } else {
                result = -1;
            }
            
            if(result > 0){ 
                swapListNode(words, cur, cur->next);
            } 
        }
    }
    
    return 0;
}

List *List_merge_sort(List *list, List_compare cmp)
{
    
    list = List_create();

    List_push(list, "test1 data");
    List_push(list, "test2 data");
    List_push(list, "test3 data");
    
    


    // Placeholder use for cmp()
    int test = cmp("hello","goodbye");
    if (test){
        return list;
    }


    return list;
}
