#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

#define MAX 512

struct address
{
    void *ptr;
    size_t size;
};

struct address pointers[MAX];
int index = 0;

void *mymalloc(size_t size)
{
    void *ptr = malloc(size);
    struct address temp;

    temp.ptr = ptr;
    temp.size = size;
    pointers[index++] = temp;

    return ptr;
}

void myfree(void *ptr)
{
    int i;

    free(ptr);
    for (i = 0; i < index; i++)
    {
        if (pointers[i].ptr != 0 && pointers[i].ptr == ptr)
        {
            pointers[i].ptr = 0;
            pointers[i].size = 0;
            break;
        }
    }
}

void print_mymalloc()
{
    int i;
    
    for (i = 0; i < index; i++)
    {
        if (pointers[i].ptr != 0)
        {
            printf("%p address %d size\n", pointers[i].ptr, (int)pointers[i].size);
        }
    }
}
#endif