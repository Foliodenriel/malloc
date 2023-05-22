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

static void		freeAddrInPage( t_page *page, void *ptr )
{
	int	res;

	res = 0;
	if (page)
	{
		res = rewireBlocksInPage( page, (t_block*)(ptr - sizeof(t_block)) );
		if (!res)
			return ; // munmap() to deallocate empty page memory Must rewire pages
	}
}

void	ft_free( void *ptr )
{
	if (ptr)
		freeAddrInPage( isValidAllocatedBasedPtr( ptr ), ptr );
}