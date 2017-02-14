/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:38:30 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/14 22:34:27 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_memory	*get_memory(void)
{
	static	t_memory *mem = NULL;

	if (!mem)
	{
		mem = mmap(0, sizeof(t_memory), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		mem->tiny = NULL;
		mem->small = NULL;
		mem->large = NULL;
	}
	if (mem == MAP_FAILED)
		return (NULL);
	return (mem);
}

void		*new_split(t_block **block, size_t size)
{
	t_block	*tmp;
	t_block *new;

	tmp = *block;
	while (tmp->next)
		tmp = tmp->next;
	new = tmp->ptr + size;
	new->ptr = (void*)new + sizeof(t_block);
	new->size = tmp->size - size - sizeof(t_block);
	tmp->size = size;
	new->is_free = 1;
	new->next = tmp->next;
	tmp->next = new;
	tmp->is_free = 0;
	return (tmp->ptr);
}

size_t		getmemlock(size_t size, struct rlimit rlp, t_memory *mem)
{
	size_t			mem_lock;
	t_block			*block;

	block = mem->small;
	mem_lock = size;
	while (block)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += block->size;
		block = block->next;
	}
	block = mem->large;
	while (block)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += block->size;
		block = block->next;
	}
	if (mem_lock > rlp.rlim_max)
		return (0);
	return (mem_lock);
}

int			getprocesslimit(size_t size, t_memory *mem)
{
	struct rlimit	rlp;
	size_t			mem_lock;
	t_block			*tiny;

	if (!mem || getrlimit(RLIMIT_RSS, &rlp) == -1)
	{
		ft_putendl("Call getrlimit failed");
		return (0);
	}
	mem_lock = size + sizeof(t_block);
	tiny = mem->tiny;
	while (tiny)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += tiny->size;
		tiny = tiny->next;
	}
	if ((mem_lock = getmemlock(mem_lock, rlp, mem)) == 0)
		ft_putendl("Process can't handle this much memory allocation");
	else
		return (mem_lock > rlp.rlim_max ? 0 : 1);
	return (0);
}
