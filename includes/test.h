/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:28:03 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/22 15:16:20 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TEST_H
# define _TEST_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <libft.h>

# define TINY		1
# define SMALL		2
# define LARGE		3

typedef struct		s_block
{
	void			*ptr;
	int				is_free;
	size_t			size;
	int				type;
	struct s_block	*next;
}					t_block;

void				*myMalloc(size_t size);
void				myFree(void	*ptr);
void				*myRealloc(void *ptr, size_t size);
void				show_alloc_mem(void);

t_block				*get_tiny_static(t_block *block, int bool);
t_block				*get_small_static(t_block *block, int bool);
t_block				*get_large_static(t_block *block, int bool);

t_block				*create_new_block(int type);
size_t				find_mem_size(size_t mem_size, size_t size);
void				split_memory(t_block *mem, size_t size, int type);

void				*check_chain(t_block **block, size_t size);
void				*finish_malloc(t_block *block, size_t size);

void				defrag(t_block *block);
void				change_static(t_block *tmp2, t_block *tmp, int type);
void				free_chain(t_block *block, size_t size_max, int type);

size_t				getprocesslimit(void);
void				show_full_mem(void);

#endif
