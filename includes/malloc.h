/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:57:31 by tlepeche          #+#    #+#             */
/*   Updated: 2017/02/14 22:31:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MALLOC_H
# define _MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdio.h>
//*# include <stdlib.h>
# include <sys/resource.h>
# include <libft.h>

# define TINY_MAX	getpagesize() / 128
# define TINY_SIZE	getpagesize() * 2

# define SMALL_MAX	getpagesize() / 4
# define SMALL_SIZE	getpagesize() * 128

# define TINY		1
# define SMALL		2
# define LARGE		3

typedef struct		s_block
{
	int				is_free;
	void			*ptr;
	size_t			size;
	struct s_block	*next;
}					t_block;

typedef	struct		s_memory
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_memory;

void				*malloc(size_t size);
void				free(void	*ptr);
void				*realloc(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				show_alloc_mem(void);

t_memory			*get_memory(void);

void				*new_split(t_block **block, size_t size);
void				defrag(t_block **block);
int					getprocesslimit(size_t size, t_memory *mem);
void				show_full_mem(void);

#endif
