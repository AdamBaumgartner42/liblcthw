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

List *List_merge(List *left, List *right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;
    
    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) { 
            if (cmp(List_first(left), List_first(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if (List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else if (List_count(right) > 0) {
            val = List_shift(right);
            List_push(result, val);
        }
    }

    return result;
}
    

List *List_merge_sort(List *list, List_compare cmp)
{
    if(List_count(list) <= 1) {
        return list;
    }

    List *left = List_create();
    List *right = List_create();
    int middle = List_count(list) / 2;

    LIST_FOREACH(list, first, next, cur){
        if (middle > 0) {
            List_push(left, cur->value);
        } else {
            List_push(right, cur->value);
        }

        middle --; 
    }

    List *sort_left = List_merge_sort(left, cmp);
    List *sort_right = List_merge_sort(right, cmp);

    if (sort_left != left){
        List_destroy(left);
    }
    if (sort_right != right){
        List_destroy(right);
    }

    return List_merge(sort_left, sort_right, cmp);

}



