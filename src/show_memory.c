/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:38:59 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/20 19:55:00 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

int		print_chain(t_block *block)
{
	int res;

	res = 0;
	while (block)
	{
		if (block->size != 0 && block->ptr)
		{
			ft_putstr("0x");
			ft_putnbr_base((long int)(block->ptr), 16);
			ft_putstr(" - 0x");
			ft_putnbr_base((long int)(block->ptr + block->size), 16);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putendl(" octets");
			res += block->size;
		}
		block = block->next;
	}
	return res;
}

void	show_alloc_mem()
{
	t_block *mem;
	int		res;

	res = 0;
	mem = get_tiny_static();
	if (mem && mem->ptr)
	{
		ft_putstr("TINY : 0x");
		ft_putnbr_base((long int)mem->ptr, 16);
		ft_putchar('\n');
		res += print_chain(mem);
	}
	mem = get_small_static();
	if (mem && mem->ptr)
	{
		ft_putstr("SMALL : 0x");
		ft_putnbr_base((long int)mem->ptr, 16);
		ft_putchar('\n');
		res += print_chain(mem);
	}
	mem = get_large_static();
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
