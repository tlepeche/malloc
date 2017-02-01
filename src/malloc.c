/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:45:12 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 20:05:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*finish_malloc(t_block *block, size_t size)
{
	if (block->ptr == MAP_FAILED)
	{
		munmap(block, sizeof(t_block *));
		return (NULL);
	}
	else
		block->is_free = 0;
	if (block->is_free == 0 && block->size > size)
		new_split_block(block, size, block->size, block->type);
	return (block);
}

void	*malloc_tiny(size_t size)
{
	t_block *tiny;
	t_block *tmp;

	tiny = get_tiny_static(NULL, 2);
	tmp = find_mem(tiny, size);
	if (tmp->ptr)
		return (tmp->ptr);
	if (!tmp)
	{
		tiny = get_tiny_static(NULL, 0);
		while (tiny->next)
			tiny = tiny->next;
		tiny->next = create_new_block(TINY);
		tiny = tiny->next;
	}
	tiny->ptr = mmap(0, TINY_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tiny->size = (size_t)(TINY_SIZE);
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

	small = get_small_static(NULL, 2);
	tmp = find_mem(small, size);
	if (tmp->ptr)
		return (tmp->ptr);
	if (!tmp)
	{
		small = get_small_static(NULL, 0);
		while (small->next)
			small = small->next;
		small->next = create_new_block(SMALL);
		small = small->next;
	}
	small->ptr = mmap(0, SMALL_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	small->size = (size_t)(SMALL_SIZE);
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

	large = get_large_static(NULL, 2);
	tmp = large;
	if (check_chain(&tmp, size))
		return (tmp->ptr);
	if (!tmp)
	{
		large = get_large_static(NULL, 0);
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

void	*malloc(size_t size)
{
	if (getprocesslimit(size) == 0)
		return (NULL);
	if (size <= (size_t)(TINY_MAX))
		return (malloc_tiny(size));
	if (size <= (size_t)(SMALL_MAX))
		return (malloc_small(size));
	else
		return (malloc_large(size));
}
