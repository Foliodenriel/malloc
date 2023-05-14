#include "ft_malloc.h"

size_t          computePageSize( char type )
{
    if (type == 0)
        return ((ALLOC_MAX_SIZE_TINY * 100) + (sizeof(t_block) * 100) + sizeof(t_page));
    else if (type == 1)
        return ((ALLOC_MAX_SIZE_SMALL * 100) + (sizeof(t_block) * 100) + sizeof(t_page));
    return (0);
}

void	show_memory_tiny( t_page *page )
{
	t_block	*blocks;

	blocks = NULL;
	printf("- TINY -\n");
	while (page)
	{
		if (page->blocks)
		{
			blocks = page->blocks;
			while (blocks)
			{
				ft_printf("%p - %p\n", (void*)((void*)blocks + sizeof(t_block)), (void*)((void*)blocks + sizeof(t_block) + blocks->size));
				blocks = blocks->next;
			}
		}
		page = page->next;
	}
}

void	show_memory()
{
	show_memory_tiny( g_alloc.tiny );
}