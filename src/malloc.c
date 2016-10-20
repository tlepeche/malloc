#include <test.h>

void	*check_chain(t_block **block, size_t size)
{
	while (*block && (*block)->ptr)
	{
		if ((*block)->is_free && (*block)->size >= size)
		{
			(*block)->is_free = 0;
			split_memory(*block, size, (*block)->type);
			print_verif(get_tiny_static());
			return ((*block)->ptr);
		}
		*block = (*block)->next;
	}
	return (NULL);
}

void	*finish_malloc(t_block * block, size_t size)
{
	if (block->ptr == MAP_FAILED)
	{
		munmap(block, sizeof(t_block *));
		return (NULL);
	}
	else
		block->is_free = 0;
	split_memory(block, size, block->type);
	print_verif(block);
	return (block);
}	

void	*malloc_tiny(size_t size)
{
	t_block *tiny;
	t_block *tmp;

	tiny = get_tiny_static();
	tmp = tiny;
	if (check_chain(&tmp, size))
		return (tmp->ptr);
	if (!tmp)
	{
		tiny = get_tiny_static();
		while (tiny->next)
			tiny = tiny->next;
		tiny->next = create_new_block(TINY);
		tiny = tiny->next;
	}
	tiny->ptr = mmap(0, getpagesize() / 64, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tiny->size = (size_t)(getpagesize() / 64);
	tiny = finish_malloc(tiny, size);
	if (tiny)
		return (tiny->ptr);
	else
		return (NULL);
}

void	*malloc_small(size_t size)
{
	t_block *small;
	t_block *tmp;

	small = get_small_static();
	tmp = small;
	if (check_chain(&tmp, size))
		return (tmp->ptr);
	if (!tmp)
	{
		small = get_small_static();
		while (small->next)
			small = small->next;
		small->next = create_new_block(SMALL);
		small = small->next;
	}
	small->ptr = mmap(0, getpagesize() / 16, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	small->size = (size_t)(getpagesize() / 16);
	small = finish_malloc(small, size);
	if (small)
		return (small->ptr);
	else
		return (NULL);
}

void	*malloc_large(size_t size)
{
	t_block *large;
	t_block *tmp;

	large = get_large_static();
	tmp = large;
	if (check_chain(&tmp, size))
		return (tmp->ptr);
	if (!tmp)
	{
		large = get_large_static();
		while (large->next)
			large = large->next;
		large->next = create_new_block(LARGE);
		large = large->next;
	}
	large->ptr = mmap(0, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	large->size = size;
	large = finish_malloc(large, size);
	if (large)
		return (large->ptr);
	else
		return (NULL);
}

void	*myMalloc(size_t size)
{
	if (size == 0 || size > getprocesslimit())
		return (NULL);
	if (size <= (size_t)(getpagesize() / 64))
		return (malloc_tiny(size));
	if (size <= (size_t)(getpagesize() / 16))
		return (malloc_small(size));
	else
		return (malloc_large(size));
}
