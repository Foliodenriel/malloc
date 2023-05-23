#include "ft_malloc.h"

size_t			computePageSize( e_pagesizetype pagesize, size_t size )
{
	int		mult;

	mult = 0;
    if (pagesize == PAGESIZETYPE_TINY)
        return ((ALLOC_MAX_SIZE_TINY * 100) + (sizeof(t_block) * 100) + sizeof(t_page));
    else if (pagesize == PAGESIZETYPE_SMALL)
        return ((ALLOC_MAX_SIZE_SMALL * 100) + (sizeof(t_block) * 100) + sizeof(t_page));
	else
	{
		size += sizeof(t_page) + sizeof(t_block);
		if (size >= (size_t)MALLOC_PAGE_SIZE)
		{
			mult = size / (size_t)MALLOC_PAGE_SIZE;
			if (size % (size_t)MALLOC_PAGE_SIZE)
				mult++;
		}
		else if (size < (size_t)MALLOC_PAGE_SIZE)
		{
			mult = (size_t)MALLOC_PAGE_SIZE / size;
			if ((size_t)MALLOC_PAGE_SIZE % size)
				mult++;
		}
		return ((size_t)(mult * (size_t)MALLOC_PAGE_SIZE));
	}
    return (0);
}

e_pagesizetype	getTypeFromSize( size_t size )
{
	if (size <= (size_t)ALLOC_MAX_SIZE_TINY)
		return (PAGESIZETYPE_TINY);
	else if (size > (size_t)ALLOC_MAX_SIZE_TINY && size <= (size_t)ALLOC_MAX_SIZE_SMALL)
		return (PAGESIZETYPE_SMALL);
	else
		return (PAGESIZETYPE_LARGE);
}

static t_page	*isAllocatedInPage( t_page *page, void *ptr )
{
	t_block	*block;

	block = NULL;
	while (page)
	{
		block = page->block;
		while (block)
		{
			if (block->data == ptr)
				return (page);
			block = block->next;
		}
		page = page->next;
	}
	return (NULL);
}

t_page			*isValidAllocatedBasedPtr( void *ptr )
{
	t_page	*page;

	page = NULL;
	if ((page = isAllocatedInPage( g_alloc.tiny, ptr )))
		return (page);
	else if ((page = isAllocatedInPage( g_alloc.small, ptr )))
		return (page);
	else if ((page = isAllocatedInPage( g_alloc.large, ptr )))
		return (page);
	return (NULL);
}

void			print_memory( void *data, size_t size, size_t len)
{
	unsigned char	*bytes;
	size_t	i;
	size_t	j;

	i = 0;
	bytes = (unsigned char*)data;
	while (i < size)
	{
		j = 0;
		ft_printf("0x%p\t:\t", &bytes[i]);
		while (j < len)
		{
			ft_printf("%0.2x ", bytes[i]);
			j++;
			i++;
		}
		i -= j;
		j = 0;
		ft_printf("\t");
		while (j < len)
		{
			if (ft_isalnum( bytes[i]))
				ft_printf("%c ", bytes[i]);
			else
				ft_printf(". ");
			i++;
			j++;
		}
		ft_printf("\n");
	}
}

static size_t	show_memory_blocks( t_page *page, int opt )
{
	t_block	*block;
	size_t	total;

	total = 0;
	block = NULL;
	while (page)
	{
		if (page->block)
		{
			block = page->block;
			while (block)
			{
				total += block->size;
				ft_printf("%p - %p : %lu bytes\n", (void*)((void*)block + sizeof(t_block)), (void*)((void*)block + sizeof(t_block) + block->size), block->size);
				if (opt)
					print_memory( block->data, block->size, opt );
				block = block->next;
			}
		}
		page = page->next;
	}
	return (total);
}

void			show_memory()
{
	size_t	total;

	total = 0;
	if (g_alloc.tiny)
	{
		ft_printf("TINY : %p\n", g_alloc.tiny);
		total += show_memory_blocks( g_alloc.tiny, 0 );
	}
	if (g_alloc.small)
	{
		ft_printf("SMALL : %p\n", g_alloc.small);
		total += show_memory_blocks( g_alloc.small, 0 );
	}
	if (g_alloc.large)
	{
		ft_printf("LARGE : %p\n", g_alloc.large);
		total += show_memory_blocks( g_alloc.large, 0 );
	}
	ft_printf("Total : %lu\n\n", total);
}

void		show_memory_ex( )
{
	size_t	total;

	total = 0;
	if (g_alloc.tiny)
	{
		ft_printf("TINY : %p\n", g_alloc.tiny);
		total += show_memory_blocks( g_alloc.tiny, 8 );
	}
	if (g_alloc.small)
	{
		ft_printf("SMALL : %p\n", g_alloc.small);
		total += show_memory_blocks( g_alloc.small, 8 );
	}
	if (g_alloc.large)
	{
		ft_printf("LARGE : %p\n", g_alloc.large);
		total += show_memory_blocks( g_alloc.large, 8 );
	}
	ft_printf("Total : %lu\n\n", total);
}