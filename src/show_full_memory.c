/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:38:59 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/22 15:45:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

static inline int		print_chain(t_block *block)
{
	int res;

	res = 0;
	while (block)
	{
		if (block->ptr)
		{
			ft_putstr("0x");
			ft_putnbr_base((long int)(block->ptr), 16);
			ft_putstr(" - 0x");
			if (block->size != 0)
				ft_putnbr_base((long int)(block->ptr + block->size - 1), 16);
			else
				ft_putnbr_base((long int)(block->ptr + block->size), 16);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			if (block->is_free)
				ft_putendl(" octets and is free");
			else
				ft_putendl(" octets and is not free");
			res += block->size;
		}
		block = block->next;
	}
	return (res);
}

static inline void		show_rest_mem(int res)
{
	t_block	*mem;

	mem = get_small_static(NULL, 0);
	if (mem && mem->ptr)
	{
		ft_putstr("SMALL : 0x");
		ft_putnbr_base((long int)mem->ptr, 16);
		ft_putchar('\n');
		res += print_chain(mem);
	}
	mem = get_large_static(NULL, 0);
	if (mem && mem->ptr)
	{
		ft_putstr("LARGE : 0x");
		ft_putnbr_base((long int)mem->ptr, 16);
		ft_putchar('\n');
		res += print_chain(mem);
	}
	ft_putstr("Total : ");
	ft_putnbr(res);
	ft_putendl(" octets");
}

void					show_full_mem(void)
{
	t_block *mem;
	int		res;

	res = 0;
	mem = get_tiny_static(NULL, 0);
	if (mem && mem->ptr)
	{
		ft_putstr("TINY : 0x");
		ft_putnbr_base((long int)mem->ptr, 16);
		ft_putchar('\n');
		res += print_chain(mem);
	}
	show_rest_mem(res);
}
