/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/17 19:15:30 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

void	myFree(void *ptr)
{
	t_block *mem;
	
	if (!ptr)
		return ;
	mem = get_static();
	while (mem)
	{
		if (mem->ptr == ptr)
		{
			if (munmap(mem->ptr, mem->size) == -1)
				printf("ca a merder\n");
			mem->is_free = 1;
			break;
		}
		mem = mem->next;
	}
}
