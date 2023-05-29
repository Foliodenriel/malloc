#include "ft_malloc.h"

static int		rewireBlocksInPage( t_page *page, t_block *block)
{
	if (!block->prev)
	{
		page->block = block->next;
		if (block->next)
			block->next->prev = NULL;
	}
	else if (block->prev)
	{
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
	}
	if (!page->block)
		return (0);
	return (1); // Used to munmap memory if page has now no block
}

static void		rewirePages(t_page *deleted_page)
{
	t_page **first_page;

	first_page = NULL;
	if (!deleted_page)
		return ;
	if (deleted_page->type == PAGESIZETYPE_TINY)
		first_page = &g_alloc.tiny;
	if (deleted_page->type == PAGESIZETYPE_SMALL)
		first_page = &g_alloc.small;
	if (deleted_page->type == PAGESIZETYPE_LARGE)
		first_page = &g_alloc.large;
	if (deleted_page->prev)
	{
		deleted_page->prev->next = deleted_page->next;
		deleted_page->next->prev = deleted_page->prev;
	}
	else
		*first_page = deleted_page->next;
	
}

static void		freeAddrInPage( t_page *page, void *ptr )
{
	int	res;

	res = 0;
	if (page)
	{
		res = rewireBlocksInPage( page, (t_block*)(ptr - sizeof(t_block)) );
		if (!res)
		{
			rewirePages( page );
			munmap(page, page->size);
			return ; // munmap() to deallocate empty page memory Must rewire pages
		}
	}
}

void	ft_free( void *ptr )
{
	if (ptr)
	{
		pthread_mutex_lock(&g_alloc_mutex);
		freeAddrInPage( isValidAllocatedBasedPtr( ptr ), ptr );
		pthread_mutex_unlock(&g_alloc_mutex);
	}
}