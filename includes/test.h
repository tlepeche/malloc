/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:28:03 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/17 19:17:37 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H_
# define TEST_H_

#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

typedef struct		s_block
{
	void			*ptr;
	int				is_free;
	size_t			size;
	struct s_block	*next;
}					t_block;

t_block				*create_new_block(void);
void				create_new_split_block(t_block *mem, size_t tmp_size, size_t size);
size_t				find_mem_size(size_t mem_size, size_t size);
void				split_memory(t_block *mem, size_t size);
void				*myMalloc(size_t size);
t_block				*get_static(void);

void				print_verif(t_block *mem);
void				myFree(void	*ptr);

#endif
