#ifndef __FT_MALLOC_H__
# define __FT_MALLOC_H__

# include "libft.h"
# include "ft_printf.h"
# include <sys/mman.h>

# include <stdio.h>

# define MALLOC_PAGE_SIZE getpagesize()

# define ALLOC_MAX_SIZE_TINY (MALLOC_PAGE_SIZE / 32)
# define ALLOC_MAX_SIZE_SMALL (MALLOC_PAGE_SIZE / 16)

typedef struct      s_block
{
    short           checkcode;
    size_t          size;
    struct s_block  *next;
    struct s_block  *prev;

}                   t_block;

typedef struct      s_page
{
    t_block         *blocks;
    char            type; // 0 tiny | 1 small | 2 large
    struct s_page   *next;
}                   t_page;

// Global variable structure
typedef struct      s_alloc
{
    t_page          *tiny;
    t_page          *small;
    t_page          *large;
}                   t_alloc;

t_alloc             g_alloc;

void        *allocate( t_page **page, size_t size, char type );
void        *ft_malloc( size_t size );
size_t      computePageSize( char type );
void        show_memory();
// void        *realloc(void *ptr, size_t size);
void        ft_free( void *ptr );

#endif