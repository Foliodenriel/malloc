#ifndef __FT_MALLOC_H__
# define __FT_MALLOC_H__

# include "libft.h"
# include "ft_printf.h"
# include <sys/mman.h>

# include <stdio.h>

# define MALLOC_PAGE_SIZE getpagesize()

# define ALLOC_MAX_SIZE_TINY (MALLOC_PAGE_SIZE / 32)
# define ALLOC_MAX_SIZE_SMALL (MALLOC_PAGE_SIZE / 8)

typedef enum            pagesizetype {
    PAGESIZETYPE_TINY   = 1,
    PAGESIZETYPE_SMALL  = 2,
    PAGESIZETYPE_LARGE  = 4
}                       e_pagesizetype;

typedef struct          s_block
{
    size_t              size;
    void                *data;
    struct s_block      *next;
    struct s_block      *prev;

}                       t_block;

typedef struct          s_page
{
    t_block             *block;
    e_pagesizetype      type; // 0 tiny | 1 small | 2 large
    struct s_page       *next;
    struct s_page       *prev;
}                       t_page;

// Global variable structure
typedef struct          s_alloc
{
    t_page              *tiny;
    t_page              *small;
    t_page              *large;
}                       t_alloc;

t_alloc                 g_alloc;

// Side functions
t_page                  *isValidAllocatedBasedPtr( void *ptr );
size_t                  computePageSize( e_pagesizetype pagesize, size_t size );
e_pagesizetype	        getTypeFromSize( size_t size );
void                    show_memory( );

// Main functions
void                    *ft_allocate( t_page **page, size_t size, e_pagesizetype type );
void                    *ft_malloc( size_t size );
void                    *ft_realloc( void *ptr, size_t size );
void                    ft_free( void *ptr );

#endif