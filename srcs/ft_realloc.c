#include "ft_malloc.h"

// May grow or decrease current allocation size, in case it decrease or grow
// No the old useless block or newly allocated block wouldn't be initialized

static void		*growCurrentAllocation( t_page *page, t_block *block, size_t size )
{
	if (block->next)
	{
		if ((size_t)((void*)block->next - block->data) >= size)
		{
			block->size = size;
			return (block->data);
		}
	}
	else
	{
		if ((size_t)(((void*)page + computePageSize( page->type, size )) - block->data) >= size)
		{
			block->size = size;
			return (block->data);
		}
	}
	return (NULL);
}

static void		*updateCurrentAllocation( void *ptr, size_t size )
{
	t_page	*page;
	t_block	*block;

	block = NULL;
	page = NULL;
	if (!ptr)
		return (NULL);
	page = isValidAllocatedBasedPtr( ptr );
	if (page)
	{
		block = (t_block*)(ptr - sizeof(t_block));
		if (block->size > size && (page->type == getTypeFromSize( size )))
		{
			block->size = size;
			return (block->data);
		}
		else if (block->size < size && (page->type == getTypeFromSize( size )))
			return (growCurrentAllocation( page, block, size ));
		else if (block->size == size)
			return (block->data); // Here we do nothing and return same data space
	}
	return (NULL);
}

// If ptr is NULL, must allocated size DONE
// If size is < to ptr size must reduce ptr size
// 
void        *ft_realloc( void *ptr, size_t size )
{
	t_block	*block;
	void	*new_ptr;

	new_ptr = NULL;
	pthread_mutex_lock(&g_alloc_mutex);
	if (size == 0 && ptr)
	{
		ft_free( new_ptr );
		return (NULL);
	}
	new_ptr = updateCurrentAllocation( ptr, size ); // Try to update allocation
	if (!new_ptr)
	{
		block = (t_block*)(ptr - sizeof(t_block));
		new_ptr = ft_malloc( size ); // If failed then alloc
		ft_memcpy(new_ptr, block->data, block->size);
	}

	// copy

	if (ptr && new_ptr && (ptr != new_ptr))
		ft_free(ptr); // Free old pointer if new_ptr is at some other place in memory
	pthread_mutex_unlock(&g_alloc_mutex);
	return (new_ptr);
}