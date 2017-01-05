/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:38:30 by tlepeche          #+#    #+#             */
/*   Updated: 2017/01/05 18:43:49 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

void	*check_chain(t_block **block, size_t size)
{
	while (*block && (*block)->ptr)
	{
		if ((*block)->is_free && (*block)->size >= size)
		{
			(*block)->is_free = 0;
			split_memory(*block, size, (*block)->type);
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

void	split_memory(t_block *mem, size_t size, int type)
{
	if (mem->is_free == 0 && mem->size > size)
		new_split_block(mem, size, mem->size, type);
}

// A RETRAVAILLER
// QUE LA MAILLON SOIT FREE OU PAS POUR L'UTILISATEUR, IL EST QUAND MEME ALLOUE
// AU NIVEAU SYSTEM DONC COMPTER.
int		getprocesslimit(size_t size)
{
	struct rlimit	rlp;
	t_block			*mem;
	size_t			mem_lock;
	int				free;

	free = 0;
	mem = get_tiny_static(NULL, 0);
	mem_lock = 0;
	while (mem)
	{
		if (mem->size > size && mem->is_free && size <= (size_t)(getpagesize() / 128))
			free = 1;
		mem_lock += mem->size;
		mem = mem->next;
	}
	mem = get_small_static(NULL, 0);
	while (mem)
	{
		if (mem->size > size && mem->is_free &&
				size <= (size_t)(getpagesize() / 4) && size > (size_t)(getpagesize() / 128))
			free = 1;
		mem_lock += mem->size;
		mem = mem->next;
	}
	mem = get_large_static(NULL, 0);
	while (mem)
	{
		if (mem->size > size && mem->is_free && size > (size_t)(getpagesize() / 4))
			free = 1;
		mem_lock += mem->size;
		mem = mem->next;
	}

	if (getrlimit(RLIMIT_MEMLOCK, &rlp) == -1)
		ft_putendl("Call getrlimit failed");
	else
		return (mem_lock > rlp.rlim_max);
	return (0);
}
