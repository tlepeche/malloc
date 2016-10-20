#include <test.h>

t_block	*create_new_block(int type)
{
	t_block *mem_block;
	mem_block = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem_block == MAP_FAILED)
		return (NULL);
	mem_block->type = type;
	mem_block->ptr = NULL;
	mem_block->is_free = 1;
	mem_block->size = 0;
	mem_block->next = NULL;
	return (mem_block);
}

void	create_new_split_block(t_block *mem, size_t tmp_size, size_t size, int type)
{
	t_block *tmp_next;
	t_block *tmp;

	mem->size = tmp_size;
	tmp = mem;
	tmp_next = (t_block *)mmap(0, sizeof(t_block), PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp_next->type = type;
	tmp_next->ptr = mem->ptr + tmp_size + 1;
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

void	split_memory(t_block *mem, size_t size, int type)
{
	size_t	tmp_size;

	tmp_size = find_mem_size(mem->size, size);
	if (mem->is_free == 0 && mem->size > size &&
			tmp_size != 0 && tmp_size < mem->size)
		create_new_split_block(mem, tmp_size, mem->size, type);
}

size_t		getprocesslimit(void)
{
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_DATA, &rlp) == -1)
		ft_putendl("Call getrlimit failed");
	else
		return (rlp.rlim_max);
	return (0);
}
