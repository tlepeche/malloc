/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:38:30 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/02 15:59:03 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*check_chain(t_block **block, size_t size)
{
	while (*block && (*block)->ptr)
	{
		if ((*block)->is_free && (*block)->size >= size)
		{
			(*block)->is_free = 0;
			if ((*block)->is_free == 0 && (*block)->size > size)
				new_split_block(*block, size, (*block)->size, (*block)->type);
			return ((*block)->ptr);
		}
		*block = (*block)->next;
	}
	return (NULL);
}

t_block	*create_new_block(int type)
{
	t_block *mem_block;

	mem_block = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem_block == MAP_FAILED)
		return (NULL);
	mem_block->type = type;
	mem_block->ptr = NULL;
	mem_block->is_free = 1;
	mem_block->size = 0;
	mem_block->next = NULL;
	return (mem_block);
}

void	new_split_block(t_block *mem, size_t tmp_size, size_t size, int type)
{
	t_block *tmp_next;

	mem->size = tmp_size;
	tmp_next = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp_next->type = type;
	tmp_next->ptr = mem->ptr + tmp_size;
	tmp_next->size = size - tmp_size;
	tmp_next->is_free = 1;
	tmp_next->next = mem->next;
	mem->next = tmp_next;
}

size_t	getmemlock(size_t size, struct rlimit rlp)
{
	t_block			*mem;
	size_t			mem_lock;

	mem_lock = size;
	mem = get_small_static(NULL, 0);
	while (mem)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += mem->size;
		mem = mem->next;
	}
	mem = get_large_static(NULL, 0);
	while (mem)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += mem->size;
		mem = mem->next;
	}
	if (mem_lock > rlp.rlim_max)
		return (0);
	return (mem_lock);
}

int		getprocesslimit(size_t size)
{
	struct rlimit	rlp;
	size_t			mem_lock;
	t_block			*mem;

	if (getrlimit(RLIMIT_RSS, &rlp) == -1)
	{
		ft_putendl("Call getrlimit failed");
		return (0);
	}
	mem_lock = size;
	mem = get_tiny_static(NULL, 0);
	while (mem)
	{
		if (mem_lock > rlp.rlim_max)
			return (0);
		mem_lock += mem->size;
		mem = mem->next;
	}
	if ((mem_lock = getmemlock(mem_lock, rlp)) == 0)
		ft_putendl("Process can't handle this much memory allocation");
	else
		return (mem_lock > rlp.rlim_max ? 0 : 1);
	return (0);
}
