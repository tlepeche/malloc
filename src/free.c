/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/23 18:26:06 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	defrag(t_block **block)
{
	t_block *tmp;
	t_block *prev;

	if (!((*block) && (*block)->next))
		return ;
	tmp = (*block)->next;
	prev = *block;
	while (prev->next)
	{
		if (prev->is_free && tmp && tmp->is_free &&
				(prev->ptr + prev->size == tmp))
		{
			prev->next = tmp->next;
			prev->size += tmp->size + sizeof(t_block);
		}
		else
			prev = tmp;
		tmp = tmp->next;
	}
}

int		free_block(t_block **block, void *ptr)
{
	t_block	*tmp;

	tmp = *block;
	while (tmp)
	{
		if (tmp->ptr == ptr && tmp->is_free == 0)
		{
			tmp->is_free = 1;
			defrag(block);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int		free_large(t_block **block, void *ptr)
{
	t_block	*large;
	t_block	*tmp;

	large = *block;
	tmp = NULL;
	while (large)
	{
		if (large->ptr == ptr && large->is_free == 0)
		{
			if (tmp)
				tmp->next = large->next;
			else
				*block = large->next;
			munmap(large->ptr, large->size);
			return (1);
		}
		tmp = large;
		large = large->next;
	}
	return (0);
}

void	free(void *ptr)
{
	t_memory	*mem;

	if (!ptr)
		return ;
	mem = get_memory();
	if (free_block(&(mem->tiny), ptr) == 1)
		return ;
	if (free_block(&(mem->small), ptr) == 1)
		return ;
	else if (free_large(&(mem->large), ptr) == 1)
		return ;
}
