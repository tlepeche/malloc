/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 21:44:37 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 17:01:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block	*get_tiny_static(t_block *block, int idx)
{
	static t_block *tiny_block = NULL;

	if (idx == 1)
		tiny_block = block;
	else if (tiny_block == NULL && idx == 2)
		tiny_block = create_new_block(TINY);
	return (tiny_block);
}

t_block	*get_small_static(t_block *block, int idx)
{
	static t_block *small_block = NULL;

	if (idx == 1)
		small_block = block;
	else if (small_block == NULL && idx == 2)
		small_block = create_new_block(SMALL);
	return (small_block);
}

t_block	*get_large_static(t_block *block, int idx)
{
	static t_block *large_block = NULL;

	if (idx == 1)
		large_block = block;
	else if (large_block == NULL && idx == 2)
		large_block = create_new_block(LARGE);
	return (large_block);
}
