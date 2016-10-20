/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/20 19:27:18 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <test.h>

void	myFree(void *ptr)
{
	t_block *mem;

//	if (!ptr)
		return ;
//	mem = get_static();
	while (mem)
	{
		if (mem->ptr == ptr)
		{
			if (mem->is_free == 0)
			{
				if (munmap(mem->ptr, mem->size) == -1)
					printf("munmap error, couldn't free %p addr\n", ptr);
				else
					printf("%p addr has been freed\n", ptr);
				mem->is_free = 1;
			}
			else
			{
				printf("pointer beeing freed was not allocated\n");
				exit(0);
			}
			break;
		}
		mem = mem->next;
	}
}
