#include <stdio.h>
#include <test.h>

t_block	*create_new_block(void)
{
	t_block *mem_block;
	mem_block = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem_block == MAP_FAILED)
		return (NULL);
	mem_block->ptr = NULL;
	mem_block->is_free = 1;
	mem_block->size = 0;
	mem_block->next = NULL;
	return (mem_block);
}

void	create_new_split_block(t_block *mem, size_t tmp_size, size_t size)
{
	t_block *tmp_next;
	t_block *tmp;

	mem->size = tmp_size;
	tmp = mem;
	tmp_next = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp_next->ptr = mem->ptr + tmp_size;
	tmp_next->size = size - tmp_size;
	tmp_next->is_free = 1;
	tmp_next->next = mem->next;
	mem->next = tmp_next;
}

size_t	find_mem_size(size_t mem_size, size_t size)
{
	size_t res;

	res = 1;
	while (res < size)
		res <<= 1;
	if (res > mem_size)
		return (-1);
	return res;
}

void	split_memory(t_block *mem, size_t size)
{
	size_t	tmp_size;

	tmp_size = find_mem_size(mem->size, size);
	if (mem->is_free == 0 && mem->size > size &&
			tmp_size != 0 && tmp_size < mem->size)
		create_new_split_block(mem, tmp_size, mem->size);
}

void	*myMalloc(size_t size)
{
	t_block	*mem;
	t_block	*tmp;

	if (size == 0 || size > 4096)
		return (NULL);
	mem = get_static();
	tmp = mem;
	while (tmp && tmp->ptr)
	{
		if (tmp->is_free && tmp->size >= size)
		{
			tmp->is_free = 0;
			split_memory(tmp, size);
			print_verif(mem);
			return (tmp->ptr);
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = mem;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_new_block();
		tmp = tmp->next;
	}
	if (size <= (size_t)(getpagesize() / 64))
	{
		printf("memory allocated : %d\n",getpagesize() / 64);
		tmp->ptr = mmap(0, getpagesize() / 64, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->size = (size_t)(getpagesize() / 64);
	}
	else if (size <= (size_t)(getpagesize() / 16))
	{
		printf("memory allocated : %d\n", getpagesize() / 16);
		tmp->ptr = mmap(0, getpagesize() / 16, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->size = (size_t)(getpagesize() / 16);
	}
	else
	{
		printf("memory allocated : %zu\n",size);
		tmp->ptr = mmap(0, size, PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_PRIVATE, -1, 0);
		tmp->size = size;
	}
	if (tmp->ptr == MAP_FAILED)
	{
		munmap(tmp, sizeof(t_block *));
		return (NULL);
	}
	else
		tmp->is_free = 0;
	split_memory(tmp, size);
	print_verif(mem);
	return (tmp->ptr);
}
