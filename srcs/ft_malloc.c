#include "ft_malloc.h"

void    *ft_malloc( size_t size )
{
    void    *data;

    data = NULL;
    if (size > 0)
    {
        if (size <= (size_t)ALLOC_MAX_SIZE_TINY)
            data = ft_allocate( &g_alloc.tiny, size, PAGESIZETYPE_TINY );
        else if (size <= (size_t)ALLOC_MAX_SIZE_SMALL)
            data = ft_allocate( &g_alloc.small, size, PAGESIZETYPE_SMALL );
        else
            data = ft_allocate( &g_alloc.large, size, PAGESIZETYPE_LARGE );
    }
    return (data);
}