#include "ft_malloc.h"

t_alloc         g_alloc;
pthread_mutex_t g_alloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void            *ft_malloc( size_t size )
{
    void    *data;

    data = NULL;
    pthread_mutex_lock(&g_alloc_mutex);
    if (size > 0)
    {
        if (size <= (size_t)ALLOC_MAX_SIZE_TINY)
            data = ft_allocate( &g_alloc.tiny, size, PAGESIZETYPE_TINY );
        else if (size <= (size_t)ALLOC_MAX_SIZE_SMALL)
            data = ft_allocate( &g_alloc.small, size, PAGESIZETYPE_SMALL );
        else
            data = ft_allocate( &g_alloc.large, size, PAGESIZETYPE_LARGE );
    }
    pthread_mutex_unlock(&g_alloc_mutex);
    return (data);
}