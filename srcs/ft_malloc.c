#include "ft_malloc.h"


void    *tinyAlloc( size_t size )
{
    void    *data_addr;
    // data_addr = ft_allocate();

    data_addr = NULL;
    (void)size;
    return (data_addr);
}

void    *smallAlloc( size_t size )
{
    (void)size;
    return (NULL);
}

void    *largeAlloc( size_t size )
{
    (void)size;
    return (NULL);
}

void    *ft_malloc( size_t size )
{
    void    *data;

    data = NULL;
    if (size <= (size_t)ALLOC_MAX_SIZE_TINY)
    {
        data = allocate( &g_alloc.tiny, size, 0 );
        // Allocate tiny
    }
    else if (size <= (size_t)ALLOC_MAX_SIZE_SMALL)
    {
        // allocate small
    }
    else
    {
        // Allocate Large data one page for all
    }
    return (data);
}