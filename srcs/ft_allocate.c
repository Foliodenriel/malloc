#include "ft_malloc.h"

static void     setBlockAddrAndValue( t_block **block, void *addr, t_block *n, t_block *p, size_t size )
{
    *block = (t_block*)addr;
    (*block)->size = size;
    (*block)->checkcode = -421;
    (*block)->n = n;
    (*block)->p = p;
}

static void     *getFirstAvailableSpace( t_page *page, size_t size )
{
    t_block *tmp;
    t_block *blocks;
    void    *data;

    data = NULL;
    blocks = page->blocks;
    if (!blocks)
    {
        printf("- First block -\n");
        setBlockAddrAndValue( &page->blocks, (void*)page + sizeof(t_page), NULL, NULL, size );
        page->blocks = (void*)page + sizeof(t_page);
        page->blocks->size = size;
        page->blocks->checkcode = -421;
        page->blocks->next = NULL;
        page->blocks->prev = NULL;
        data = (void*)page->blocks + sizeof(t_block);
        return (data);
    }
    else {
        printf("- Loop block -\n");
        // 42CD - Check if can insert block between page + sizeof(page) and first block
        if ()
        while (blocks->next)
        {
            if ((blocks->next - blocks + size + sizeof(t_block)) >= size + sizeof(t_block))
            {
                tmp = blocks->next;
                blocks->next = (void*)blocks + sizeof(t_block) + blocks->size;
                blocks->next->size = size;
                blocks->checkcode = -421;
                blocks->next->next = tmp;
                data = (void*)((void*)blocks + sizeof(t_block));
                return (data);
            }
        }
    }
    if (((void*)page + (size_t)computePageSize( page->type ) - (void*)blocks + sizeof(t_block) + blocks->size) >= size + sizeof(t_block))
    {
        printf("- Last block -\n");
        blocks->next = (void*)blocks + sizeof(t_block) + blocks->size;
        blocks->next->size = size;
        blocks->checkcode = -421;
        blocks->next->next = NULL;
        data = (void*)((void*)blocks->next + sizeof(t_block));
    }
    return (data);
}

static void     *queryDataSpace( t_page *page, size_t size )
{
    void    *offset;

    offset = NULL;
    if (!page)
        return (NULL);
    else {
        while (page)
        {
            offset = getFirstAvailableSpace( page, size );
            page = page->next;
        }
    }
    return (offset);
}

void            *allocate( t_page **page, size_t size, char type )
{
    void    *data;

    data = NULL;
    data = queryDataSpace( *page, size );
    if (*page)
    {
        while ((*page)->next)
            *page = (*page)->next;
    }
    if (!data)
    {
        data = mmap(NULL, computePageSize( type ), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        *page = (t_page*)data;
        (*page)->blocks = NULL;
        (*page)->type = type;
        (*page)->next = NULL;
        data = queryDataSpace( *page, size );
    }
    return (data);
}