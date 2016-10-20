/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 18:51:09 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/20 20:11:32 by tlepeche         ###   ########.fr       */
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
				/////UTILISATION DU MUNMAP UNIQUEMENT LORSQUE TOUTE LA CHAINE ALOUER ET VIDE
				///// A FAIRE : JOINDRE 2 MAILLONS LORSQUILS SONT FREE TOUT LES 2 ET ADJACENT;
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
