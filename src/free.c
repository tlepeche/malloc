/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/21 22:16:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

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

int		free_tiny(void *ptr)
{
	t_block	*tiny;

	tiny = get_tiny_static(NULL, 0);
	while (tiny)
	{
		if (tiny->ptr == ptr)
		{
			if (tiny->is_free == 0)
			{
				tiny->is_free = 1;
				tiny = get_tiny_static(NULL, 0);
				defrag(tiny);
				free_chain(tiny, getpagesize(), TINY);
				return (1);
			}
		}
		tiny = tiny->next;
	}
	return (0);
}

int		free_small(void *ptr)
{
	t_block	*small;

	small = get_small_static(NULL, 0);
	while (small)
	{
		if (small->ptr == ptr)
		{
			if (small->is_free == 0)
			{
				small->is_free = 1;
				return (1);
			}
		}
		small = small->next;
	}
	return (0);
}

int		free_large(void *ptr)
{
	t_block	*large;
	t_block	*tmp;

	large = get_large_static(NULL, 0);
	tmp = NULL;
	while (large)
	{
		if (large->ptr >= ptr && ptr < (large->ptr + large->size))
		{
			if (large->is_free == 0)
			{
				munmap(large->ptr, large->size);
				change_static(large, tmp, LARGE);
				return (1);
			}
		}
		tmp = large;
		large = large->next;
	}
	return (0);
}

void	myFree(void *ptr)
{
	if (!ptr)
		return ;
	if (free_tiny(ptr))
		return ;
	if (free_small(ptr))
		return ;
	else if (free_large(ptr))
		return ;
	else
	{
		ft_putstr("malloc: *** error for object ");
		ft_putstr("0x");
		ft_putnbr_base((long int)ptr, 16);
		ft_putendl(": pointer being freed was not allocated");
		ft_putendl("*** set a breakpoint in malloc_error_break to debug");
		exit(0);
	}
}
