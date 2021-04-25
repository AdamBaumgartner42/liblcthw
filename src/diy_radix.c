#include <stdio.h>

int ones_sort( int *arr, int count )
{
    //test: //printf("%d\n", arr[4]);

    // Print out all the one values

    for (int i = 0; i < count; i++){
        printf("raw: %d, ones: %d\n", arr[i], arr[i]%10);
    }

    return 0;
}
