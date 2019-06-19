#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int stringCmp(const void* a, const void* b);
int stringCmpb(const void* key, const void* pelem);

int main()
{
    int count = 5;
    char** strings = malloc(5*sizeof(char*));
    for (int i = 0; i < 5; i++){
        char* buffer = malloc(30*sizeof(char));
        scanf("%s", buffer);
        strings[i] = buffer;
    }
    
    printf("\n");
    for(int i = 0; i < count; i++) printf("%s\n", strings[i]);
    
    printf("\n");
    qsort(strings, count, sizeof(char*), stringCmp); //(int(*)(const void*, const void*))strcmp
    
    printf("\n");
    for(int i = 0; i < count; i++) printf("%s\n", strings[i]);

    /*==================================================================================*\
     *char* key = "keykey";                                                             *
     *char** keyp = bsearch(key, strings, count, sizeof(char*), stringCmpb);            *
     *if (keyp == NULL) printf("there is no key\n");                                    *
     *else printf("key is %ld\n", ((void*)keyp - (void*)strings)/sizeof(char*)+1);      *
    \*==================================================================================*/

    printf("\n\n\n%p, %p\n", key, &key);
    printf("\n\n\n%p, %p\n", strings, strings[2]);
    return 0;
}




int stringCmp(const void* key, const void* pelem){
    return strcmp(*(char**)key, *(char**)pelem);
}

int stringCmpb(const void* key, const void* pelem){
    return strcmp((char*)key, *(char**)pelem);
}
