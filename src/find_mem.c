/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 15:49:17 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 19:44:45 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block	*find_mem(t_block *block, size_t size)
{
	t_block *tmp;

	tmp = block;
	if (check_chain(&tmp, size))
		return (tmp);
	if (!tmp)
	{
		defrag(block);
		tmp = block;
		if (check_chain(&tmp, size))
			return (tmp);
	}
	return (tmp);
}
