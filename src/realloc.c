/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:03:47 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 18:53:32 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block	*find_ptr(void *ptr)
{
	t_block *block;

	block = get_tiny_static(NULL, 2);
	while (block)
	{
		if (block->ptr == ptr)
			return (block);
		block = block->next;
	}
	block = get_small_static(NULL, 2);
	while (block)
	{
		if (block->ptr == ptr)
			return (block);
		block = block->next;
	}
	block = get_large_static(NULL, 2);
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
	if ((*block)->size == size)
		return (1);
	if ((*block)->size > size)
	{
		new_split_block((*block), size, (*block)->size, (*block)->type);
		return (1);
	}
	return (0);
}

int		is_ok(t_block *block, unsigned int new_size)
{
	if ((block->type == TINY && new_size <= (size_t)TINY_MAX) ||
			(block->type == SMALL && new_size <= (size_t)SMALL_MAX))
		return (1);
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	t_block	*tmp;
	void	*new_ptr;

	if ((block = find_ptr(ptr)) == NULL)
		return (NULL);
	if (stupid_realloc(&block, size))
		return (block->ptr);
	if (block->next && block->next->is_free &&
			(block->size + block->next->size) >= size && is_ok(block, size))
	{
		block->size += block->next->size;
		tmp = block->next;
		block->next = tmp->next;
		munmap(tmp, sizeof(t_block));
		block = finish_malloc(block, size);
		return (block->ptr);
	}
	else
	{
		new_ptr = malloc(size);
		new_ptr = memcpy(new_ptr, ptr, block->size);
		free(ptr);
		return (new_ptr);
	}
}
