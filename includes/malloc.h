/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:57:31 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/01 19:05:03 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MALLOC_H
# define _MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/resource.h>
# include <libft.h>

# define TINY_MAX	getpagesize() / 128
# define TINY_SIZE	getpagesize()

# define SMALL_MAX	getpagesize() / 4
# define SMALL_SIZE	getpagesize() * 32

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

void				*malloc(size_t size);
void				free(void	*ptr);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem(void);

t_block				*get_tiny_static(t_block *block, int bool);
t_block				*get_small_static(t_block *block, int bool);
t_block				*get_large_static(t_block *block, int bool);

t_block				*create_new_block(int type);
size_t				find_mem_size(size_t mem_size, size_t size);
void				new_split_block(t_block *mem, size_t s, size_t s2, int tp);

void				*check_chain(t_block **block, size_t size);
void				*finish_malloc(t_block *block, size_t size);
t_block				*find_mem(t_block *block, size_t size);

void				defrag(t_block *block);
void				change_static(t_block *tmp2, t_block *tmp, int type);
void				free_chain(t_block *block, size_t size_max, int type);

int					getprocesslimit(size_t size);
void				show_full_mem(void);

#endif
