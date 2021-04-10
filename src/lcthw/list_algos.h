#ifndef lcthw_list_algos_h
#define lcthw_list_algos_h

#include <lcthw/list.h>

typedef int (*List_compare) (const char *s1, const char *s2);

int List_bubble_sort(List *words, List_compare cmp);

List *List_merge_sort(List *words, List_compare cmp);

#endif
