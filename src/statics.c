#include <test.h>

t_block	*get_tiny_static()
{
	static t_block *tiny_block = NULL;

	if (tiny_block == NULL)
		tiny_block = create_new_block(TINY);
	return (tiny_block);
}

t_block	*get_small_static()
{
	static t_block *small_block = NULL;

	if (small_block == NULL)
		small_block = create_new_block(SMALL);
	return (small_block);
}

t_block	*get_large_static()
{
	static t_block *large_block = NULL;

	if (large_block == NULL)
		large_block = create_new_block(LARGE);
	return (large_block);
}
