/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:38:59 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/14 20:39:47 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static inline int		print_chain(t_block *block)
{
	int res;

	res = 0;
	while (block)
	{
		ft_putstr("0x");
		ft_putnbr_base((long int)(block->ptr), 16);
		ft_putstr(" - 0x");
		ft_putnbr_base((long int)(block->ptr + block->size - 1), 16);
		ft_putstr(" : ");
		ft_putnbr(block->size);
		if (block->is_free)
			ft_putendl(" octets and is free");
		else
			ft_putendl(" octets and is not free");
		res += block->size;
		block = block->next;
	}
	return (res);
}

static inline void		show_rest_mem(int res, t_memory *mem)
{
	t_block	*block;

	block = mem->small;
	if (block && block->ptr)
	{
		ft_putstr("SMALL : 0x");
		ft_putnbr_base((long int)block, 16);
		ft_putchar('\n');
		res += print_chain(block);
	}
	block = mem->large;
	if (block && block->ptr)
	{
		ft_putstr("LARGE : 0x");
		ft_putnbr_base((long int)block, 16);
		ft_putchar('\n');
		res += print_chain(block);
	}
	ft_putstr("Total : ");
	ft_putnbr(res);
	ft_putendl(" octets");
}

void					show_full_mem(void)
{
	t_memory	*mem;
	t_block		*tiny;
	int			res;

	res = 0;
	mem = get_memory();
	tiny = mem->tiny;
	if (tiny && tiny->ptr)
	{
		ft_putstr("TINY : 0x");
		ft_putnbr_base((long int)tiny, 16);
		ft_putchar('\n');
		res += print_chain(tiny);
	}
	show_rest_mem(res, mem);
}
