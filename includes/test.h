/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 17:28:03 by tlepeche          #+#    #+#             */
/*   Updated: 2016/10/20 19:17:46 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H_
# define TEST_H_

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

t_block				*get_tiny_static(void);
t_block				*get_small_static(void);
t_block				*get_large_static(void);

t_block				*create_new_block(int type);
void				create_new_split_block(t_block *mem, size_t tmp_size, size_t size, int type);
size_t				find_mem_size(size_t mem_size, size_t size);
void				split_memory(t_block *mem, size_t size, int type);
void				*myMalloc(size_t size);

void				print_verif(t_block *mem);
void				myFree(void	*ptr);
void				show_alloc_mem(void);

size_t				getprocesslimit(void);

#endif