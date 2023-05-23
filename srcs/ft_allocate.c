#include "ft_malloc.h"

t_alloc g_alloc;

static t_page   *getLastPage( t_page *page )
{
    while (page && page->next)
        page = page->next;
    return (page);
}

static t_page   *createNewPage( t_page *page, e_pagesizetype type, t_page *n, t_page *p, size_t size )
{
    page->block = NULL;
    page->type = type;
    page->next = n;
    page->prev = p;
    page->size = size;
    return (page);
}

static void     addNewPage( t_page **firstpage, t_page *page )
{
    t_page  *tmp;

    tmp = *firstpage;
    if (!tmp)
        *firstpage = page;
    else
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = page;
    }
}

static void     setBlockAddrAndValue( t_block **block, void *addr, t_block *n, t_block *p, size_t size )
{
    *block = (t_block*)addr;
    (*block)->size = size;
    (*block)->data = (void*)(*block) + sizeof(t_block);
    (*block)->next = n;
    (*block)->prev = p;
}

static void     *getFirstAvailableSpace( t_page *page, size_t size )
{
    t_block *tmp;
    t_block *block;
    void    *data;

    data = NULL;
    block = page->block;
    if (!page)
        return (NULL);
    if (!block)
    {
        setBlockAddrAndValue( &page->block, (void*)page + sizeof(t_page), NULL, NULL, size );
        data = page->block->data;
        return (data);
    }
    else {
        if ((size_t)((void*)block - ((void*)page + sizeof(t_page))) >= size + sizeof(t_block))
        {
            setBlockAddrAndValue( &page->block, (void*)page + sizeof(t_page), block, NULL, size );
            data = page->block->data;
            return (data);
        }
        while (block->next)
        {
            if ((size_t)((void*)block->next - (block->data + block->size)) >= size + sizeof(t_block))
            {
                tmp = block->next;
                setBlockAddrAndValue( &block->next, (void*)block + sizeof(t_block) + block->size, tmp, block, size );
                data = (void*)((void*)block + sizeof(t_block));
                return (data);
            }
            block = block->next;
        }
    }
    if (((void*)page + (size_t)computePageSize( page->type, size ) - (void*)block + sizeof(t_block) + block->size) >= size + sizeof(t_block))
    {
        setBlockAddrAndValue( &block->next, (void*)block + sizeof(t_block) + block->size, NULL, block, size );
        data = (void*)((void*)block->next->data);
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

void            *ft_allocate( t_page **firstpage, size_t size, e_pagesizetype type )
{
    t_page  *page;
    void    *data;
    size_t  page_size;

    data = NULL;
    page_size = 0;
    page = *firstpage;
    // Try allocate in already existing page except if type is LARGE
    if (type != PAGESIZETYPE_LARGE)
    {
        while (page)
        {
            data = queryDataSpace( page, size );
            if (data)
                return (data);
            page = page->next;
        }
    }
    // Allocate new page (always when type is LARGE)
    page_size = computePageSize( type, size );
    data = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (data)
    {
        page = createNewPage( (t_page*)data, type, NULL, getLastPage( *firstpage ), page_size );
        addNewPage( firstpage, page );
        data = queryDataSpace( page, size );
    }
    return (data);
}