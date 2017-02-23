/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 16:38:59 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/23 18:32:10 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static inline int		print_chain(t_block *bck)
{
	int res;

	res = 0;
	while (bck)
	{
		if (bck->ptr && bck->is_free == 0)
		{
			ft_putstr("0x");
			ft_putnbr_base((long long int)(bck->ptr), 16);
			ft_putstr(" - 0x");
			if (bck->size != 0)
				ft_putnbr_base((long long int)(bck->ptr + bck->size - 1), 16);
			else
				ft_putnbr_base((long long int)(bck->ptr + bck->size), 16);
			ft_putstr(" : ");
			ft_putnbr_base(bck->size, 10);
			ft_putendl(" octets");
			res += bck->size;
		}
		bck = bck->next;
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
		ft_putnbr_base((long long int)block, 16);
		ft_putchar('\n');
		res += print_chain(block);
	}
	block = mem->large;
	if (block && block->ptr)
	{
		ft_putstr("LARGE : 0x");
		ft_putnbr_base((long long int)block, 16);
		ft_putchar('\n');
		res += print_chain(block);
	}
	ft_putstr("Total : ");
	ft_putnbr_base(res, 10);
	ft_putendl(" octets");
}

void					show_alloc_mem(void)
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
		ft_putnbr_base((long long int)tiny, 16);
		ft_putchar('\n');
		res += print_chain(tiny);
	}
	show_rest_mem(res, mem);
}
