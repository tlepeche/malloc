/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 17:00:39 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	defrag(t_block *block)
{
	t_block *t;
	t_block *t2;
	int		modif;

	modif = 0;
	t = NULL;
	t2 = block;
	while (t2)
	{
		if (t && t->is_free && t2->is_free && (t->ptr + t->size) == t2->ptr)
		{
			t->size += t2->size;
			t->next = t2->next;
			munmap(t2, sizeof(t2));
			t2 = t->next;
			modif = 1;
		}
		else
		{
			t = t2;
			t2 = t2->next;
		}
	}
	if (modif == 1)
		defrag(block);
}

void	change_static(t_block *tmp2, t_block *tmp, int type)
{
	int	modif;

	modif = 0;
	if (tmp)
	{
		tmp->next = tmp2->next;
		munmap(tmp2, sizeof(t_block));
		modif = 1;
	}
	else if (tmp2->next)
	{
		tmp = tmp2->next;
		munmap(tmp2, sizeof(t_block));
	}
	if (modif == 0)
	{
		if (type == TINY)
			get_tiny_static(tmp, 1);
		else if (type == SMALL)
			get_small_static(tmp, 1);
		else
			get_large_static(tmp, 1);
	}
}

void	free_chain(t_block *block, size_t size_max, int type)
{
	t_block	*tmp;
	t_block	*tmp2;

	tmp = NULL;
	tmp2 = block;
	while (tmp2)
	{
		if (tmp2->is_free && tmp2->size == size_max)
		{
			change_static(tmp2, tmp, type);
			break ;
		}
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
}
