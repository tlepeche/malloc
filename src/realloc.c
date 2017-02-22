/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:03:47 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/22 16:34:21 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block	*find_ptr(t_memory *mem, void *ptr)
{
	t_block *block;

	block = mem->tiny;
	while (block)
	{
		if (block->ptr == ptr)
			return (block);
		block = block->next;
	}
	block = mem->small;
	while (block)
	{
		if (block->ptr == ptr)
			return (block);
		block = block->next;
	}
	block = mem->large;
	while (block)
	{
		if (block->ptr == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}

int		stupid_realloc(t_block **block, size_t size)
{
	t_block *new;

	if ((*block)->size == size)
		return (1);
	if ((*block)->size > (size + sizeof(t_block)))
	{
		new = (*block)->ptr + size;
		new->ptr = (void*)new + sizeof(t_block);
		new->size = (*block)->size - size - sizeof(t_block);
		(*block)->size = size;
		new->is_free = 1;
		new->next = (*block)->next;
		(*block)->next = new;
		defrag(block);
		return (1);
	}
	return (0);
}

int		is_ok(t_block *block, unsigned int new_size)
{
	int type;

	if (block->size <= (size_t)TINY_MAX)
		type = TINY;
	else if (block->size <= (size_t)SMALL_MAX)
		type = SMALL;
	else
		type = LARGE;
	if ((type == TINY && new_size <= (size_t)TINY_MAX) ||
			(type == SMALL && new_size <= (size_t)SMALL_MAX))
		return (1);
	return (0);
}

void	*create_new_ptr(void *ptr, size_t block_size, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	size = size < block_size ? size : block_size;
	new_ptr = ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block		*block;
	t_block		*tmp;
	t_memory	*mem;

	if (!ptr)
		return (malloc(size));
	mem = get_memory();
	if ((block = find_ptr(mem, ptr)) == NULL)
		return (NULL);
	if (block->is_free == 1)
		return (NULL);
	if (block->size <= (size_t)SMALL_MAX && stupid_realloc(&block, size))
		return (block->ptr);
	if (block->next && block->next->is_free &&
			(block->size + block->next->size) >= size && is_ok(block, size))
	{
		block->size += block->next->size + sizeof(t_block);
		tmp = block->next;
		block->next = tmp->next;
		stupid_realloc(&block, size);
		return (block->ptr);
	}
	else
		return (create_new_ptr(ptr, block->size, size));
}
