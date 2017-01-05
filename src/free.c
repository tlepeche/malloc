/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2017/01/05 18:10:36 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

void	print_error(void *ptr)
{
	ft_putstr("malloc: *** error for object ");
	ft_putstr("0x");
	ft_putnbr_base((long int)ptr, 16);
	ft_putendl(": pointer being freed was not allocated");
	ft_putendl("*** set a breakpoint in malloc_error_break to debug");
	exit(0);
}

int		free_tiny(void *ptr)
{
	t_block	*tiny;

	tiny = get_tiny_static(NULL, 0);
	while (tiny)
	{
		if (tiny->ptr <= ptr && ptr < (tiny->ptr + tiny->size))
		{
			if (tiny->is_free == 0)
			{
				tiny->is_free = 1;
				tiny = get_tiny_static(NULL, 0);
				defrag(tiny);
//				free_chain(tiny, getpagesize(), TINY);
				return (1);
			}
			print_error(ptr);
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
		if (small->ptr <= ptr && ptr < (small->ptr + small->size))
		{
			if (small->is_free == 0)
			{
				small->is_free = 1;
				small = get_small_static(NULL, 0);
//				defrag(small);
//				free_chain(small, getpagesize() * 32, SMALL);
				return (1);
			}
			print_error(ptr);
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
		if (large->ptr <= ptr && ptr < (large->ptr + large->size))
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

void	free(void *ptr)
{
	if (!ptr)
		return ;
	if (free_tiny(ptr))
		return ;
	if (free_small(ptr))
		return ;
	else if (free_large(ptr))
		return ;
}
