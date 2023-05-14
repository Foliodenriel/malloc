#include "ft_malloc.h"

static int		isInPageSection( t_page *page )
{
	while (page)
	{
		if (ptr >= (void*)(page) + sizeof(t_page) && ptr < (void)(page) + computePageSize( page->type ))
			return (1);
		page = page->next;
	}
	return (0);
}

// Get section in which ptr has it's address located
// 0 : tiny | 1 : small | 2 : large | -1 : none
static int		getValidAddressSection( void *ptr )
{
	int res;

	if ((res = isInPageSection( g_alloc.tiny )) == 1)
		return (0);
	if ((res = isInPageSection( g_alloc.tiny )) == 1)
		return (1);
	if ((res = isInPageSection( g_alloc.tiny )) == 1)
		return (2);
	return (-1);
}

void	ft_free( void *ptr )
{
	t_block *block;

	block = NULL;
	if (getValidAddressSection( ptr ) >= 0)
	{
		block = (t_block*)(ptr - sizeof(t_block));
		if (block->checkcode == -421)
		{
			// Get previous block and rewire with next block
			// Then remove this current block
		}
	}
}