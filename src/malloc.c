/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:45:12 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/23 18:00:22 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int		extend_mem(t_block **block, size_t size)
{
	t_block *tmp;

	tmp = *block;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = mmap(0, size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (tmp->next == MAP_FAILED)
		return (0);
	tmp = tmp->next;
	tmp->size = size - sizeof(t_block);
	tmp->is_free = 1;
	tmp->ptr = (void *)tmp + sizeof(t_block);
	tmp->next = NULL;
	return (1);
}

void	*malloc_block(t_block **block, size_t size, size_t size_mem)
{
	t_block *tmp;

	if (!(*block))
	{
		*block = mmap(0, size_mem, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		if (*block == MAP_FAILED)
			return (NULL);
		(*block)->size = size_mem - sizeof(t_block);
		(*block)->is_free = 1;
		(*block)->ptr = (void *)(*block) + sizeof(t_block);
		(*block)->next = NULL;
	}
	tmp = *block;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->size < size + sizeof(t_block) && extend_mem(block, size_mem) == 0)
		return (NULL);
	return (new_split(block, size));
}

void	*create_block(t_block **block, size_t size)
{
	*block = mmap(0, size + sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (*block == MAP_FAILED)
		return (NULL);
	(*block)->size = size;
	(*block)->is_free = 0;
	(*block)->ptr = (void *)(*block) + sizeof(t_block);
	(*block)->next = NULL;
	return ((*block)->ptr);
}

void	*malloc_large(t_block **block, size_t size)
{
	t_block	*tmp;
	t_block *new;

	if (!(*block))
		return (create_block(block, size));
	else
	{
		tmp = *block;
		while (tmp->next)
			tmp = tmp->next;
		new = mmap(0, size + sizeof(t_block), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		if (new == MAP_FAILED)
			return (NULL);
		tmp->next = new;
		new->size = size;
		new->is_free = 0;
		new->ptr = (void *)new + sizeof(t_block);
		new->next = NULL;
		return (new->ptr);
	}
}

void	*malloc(size_t size)
{
	t_memory	*mem;

	if ((long long int)size < 0)
		return (NULL);
	mem = get_memory();
	if (getprocesslimit(size, mem) == 0)
		return (NULL);
	if (size <= (size_t)(TINY_MAX))
		return (malloc_block(&(mem->tiny), size, TINY_SIZE));
	if (size <= (size_t)(SMALL_MAX))
		return (malloc_block(&(mem->small), size, SMALL_SIZE));
	else
		return (malloc_large(&(mem->large), size));
}
