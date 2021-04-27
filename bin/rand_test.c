#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main (void)
{
    // This program will create the same sequence of 
    // random numbes on every program run
/*  
    // rand()
    printf("rand()\n");
    for(int i = 0; i < 5; i++){ 
        printf(" %d ", rand());
    }
    printf("\n");

    // (rand() << 16)
    printf("(rand() << 16)\n");
    for(int i = 0; i < 5; i++){ 
        printf(" %d ", rand() << 16);
    }
    printf("\n");


    // (rand() | (rand() << 16))
    printf("(rand() | (rand() << 16))\n");
    for(int i = 0; i < 5; i++){ 
        printf(" %d ", (rand() | (rand() << 16)));
    }
    printf("\n");

    // (uint32_t) (rand() | rand() << 16)
    printf("(uint32_t) (rand() | (rand() << 16))\n");
    for(int i = 0; i < 5; i++){ 
        printf(" %d ", (uint32_t)(rand() | (rand() << 16)));
    }
    printf("\n");
*/
    // (uint32_t) test
    unsigned int val = 4294967295;
    unsigned int r = 3211263; 
    unsigned int b = 65535 + 1;
    uint64_t  c = 131071;
    printf("%x ", (uint32_t) RAND_MAX);
    printf("%x ", (uint32_t) val);
    printf("%u ", (uint32_t) (c)); 
    printf("%u ", (uint32_t) (c << 16)); 
    printf("%u ", (uint32_t) (c | (c << 16))); 
    printf("\n");






    return 0;
}

