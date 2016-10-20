#include <test.h>

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
		nb = 17;
	str = (char*)myMalloc(sizeof(char)*(nb + 1));	
	str2 = (char*)myMalloc(sizeof(char)*(nb *4));	
	str3 = (char*)myMalloc(sizeof(char)*(nb *52));	
	str4 = (char*)myMalloc(sizeof(char)*(14000 ));	
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
		ft_putstr("0x");
		ft_putnbr_base((long int)str, 16);
		ft_putstr(" --> ");
		ft_putendl(str);

		ft_putstr("0x");
		ft_putnbr_base((long int)str2, 16);
		ft_putstr(" --> ");
		ft_putendl(str2);

		ft_putstr("0x");
		ft_putnbr_base((long int)str3, 16);
		ft_putstr(" --> ");
		ft_putendl(str3);

		ft_putstr("0x");
		ft_putnbr_base((long int)str4, 16);
		ft_putstr(" --> ");
		ft_putendl(str4);
		ft_putchar('\n');
	}
	show_alloc_mem();
//	print_verif(get_static());
/*	myFree(str);
	myFree(str2);
	myFree(str3);
	myFree(str4);*/
	return (0);
}
