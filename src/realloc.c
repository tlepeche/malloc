/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 15:03:47 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/23 16:21:44 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

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

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	t_block	*tmp;
	void	*new_ptr;

	block = find_ptr(ptr);
	if (block == NULL)
		return (NULL);
	if (block->next && block->next->is_free &&
			(block->size + block->next->size) >= size)
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
