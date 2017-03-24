/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_full_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:30:09 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/24 18:17:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

static inline int		print_chain(t_block *block)
{
	int res;

	res = 0;
	while (block && block->ptr)
	{
		ft_putstr("0x");
		ft_putnbr_base((long long int)(block->ptr), 16);
		ft_putstr(" - 0x");
		if (block->size != 0)
			ft_putnbr_base((long long int)(block->ptr + block->size - 1), 16);
		else
			ft_putnbr_base((long long int)(block->ptr + block->size), 16);
		ft_putstr(" : ");
		ft_putnbr_base(block->size, 10);
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

void					show_full_mem(void)
{
	t_memory	*mem;
	t_block		*tiny;
	int			res;

	pthread_mutex_lock(&(g_mutex.mutex));
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
	pthread_mutex_unlock(&(g_mutex.mutex));
}
