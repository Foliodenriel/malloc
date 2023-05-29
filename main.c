#include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/mman.h>
#include "ft_printf.h"
#include "ft_malloc.h"
#include <libft.h>

#include <pthread.h>

struct test
{
    char    s[163];
};

void    *thread_malloc()
{
    ft_malloc( 10 );
}

unsigned int    ft_align(unsigned int i, unsigned int alignto)
{
    unsigned int    mask;
    size_t          offset;

    offset = 0;
    mask = (unsigned int)(0 - 1);
    while ((alignto & 1) != 1)
    {
        alignto = alignto >> 1;
        offset++;
    }
    mask = mask << offset;
    i = (i & mask) == i ? i & mask : (i & mask) + (alignto << offset); 
    return (i);
}

int main(void)
{
    unsigned int    i;

    i = 97;
    i = ft_align(i, 8);
    ft_printf("aligned : %u\n", i);

    show_alloc_mem_ex( 8 );
    
    return (0);
}