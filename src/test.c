#include <test.h>
#include <stdlib.h> /// pour atoi

void	print_verif(t_block *mem)
{
	t_block * tmp2;

	tmp2 = mem;
	printf("mem_block:\n");
	while (tmp2)
	{
		printf("mem->ptr = %p\nmem->size = %zu\n", tmp2->ptr, tmp2->size);
		tmp2 = tmp2->next;
	}
	printf("\n");
}

t_block	*get_static()
{
	static t_block *mem_block = NULL;

	if (mem_block == NULL)
		mem_block = create_new_block();
	return (mem_block);
}

int main(int ac, char **av)
{
	int		nb;
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;
	int		i;

	(void)ac;
	if (av[1])
		nb = atoi(av[1]);
	else
		nb = 5;
	str = (char*)myMalloc(sizeof(char)*(nb + 1));	
	str2 = (char*)myMalloc(sizeof(char)*(nb + 1));	
	myFree(str2);
	str3 = (char*)myMalloc(sizeof(char)*(nb + 1));	
	str4 = (char*)myMalloc(sizeof(char)*(nb + 1));	
	if (str == NULL)
		printf("null\n");
	else
	{
		for (i = 0 ; i < nb ; i++)
		{
			str[i] = ((i + 1) % 10) + 48;
			str2[i] = ((i + 1) % 10) + 48;
			str3[i] = ((i + 1) % 10) + 48;
			str4[i] = ((i + 1) % 10) + 48;
		}
		str[i] = '\0';
		str2[i] = '\0';
		str3[i] = '\0';
		str4[i] = '\0';
		printf("%p  --> %s\n", str, str);
		printf("%p  --> %s\n", str2, str2);
		printf("%p  --> %s\n", str3, str3);
		printf("%p  --> %s\n", str4, str4);
	}
	myFree(str2);
	myFree(str3);
	myFree(str4);
	printf("pagesize = %d\n", getpagesize());
	return (0);
}
