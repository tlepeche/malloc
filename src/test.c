#include <test.h>

void	test_malloc()
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	printf("malloc str de 16 octets\n");
	str = (char*)malloc(sizeof(char) * 16);	
	printf("malloc str2 de 1257 octets\n");
	str2 = (char*)malloc(sizeof(char) * 1257);	
	printf("malloc str3 de 327 octets\n");
	str3 = (char*)malloc(sizeof(char) * 327);	
	printf("malloc str4 de 42 octets\n\n");
	str4 = (char*)malloc(sizeof(char) * 42);	
	printf("Allocated memory:\n");
	show_alloc_mem();
	printf("\nFull process memory\n");
	show_full_mem();
}

void	test_realloc()
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	printf("malloc str de 16 octets\n");
	str = (char*)malloc(sizeof(char) * 16);	
	printf("malloc str2 de 1257 octets\n");
	str2 = (char*)malloc(sizeof(char) * 1257);	
	printf("malloc str3 de 327 octets\n");
	str3 = (char*)malloc(sizeof(char) * 327);	
	printf("malloc str4 de 42 octets\n\n");
	str4 = (char*)malloc(sizeof(char) * 42);	

	printf("Allocated memory:\n");
	show_alloc_mem();
	printf("\nFull process memory\n");
	show_full_mem();

	printf("\nrealloc str de 27 octets\n");
	str = (char *)realloc(str, sizeof(char) * 27);
	printf("realloc str2 de 1337 octets\n");
	str2 = (char *)realloc(str2, sizeof(char) * 1337);
	printf("realloc str4 de 57 octets\n");
	str4 = (char *)realloc(str4, sizeof(char) * 57);
	printf("realloc str3 de 333 octets\n\n");
	str3 = (char *)realloc(str3, sizeof(char) * 333);

	printf("Allocated memory:\n");
	show_alloc_mem();
	printf("\nFull process memory\n");
	show_full_mem();
}

void	test_free()
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	printf("malloc str de 16 octets\n");
	str = (char*)malloc(sizeof(char) * -1);	
	printf("malloc str2 de 1257 octets\n");
	str2 = (char*)malloc(sizeof(char) * 1257);	
	printf("malloc str3 de 327 octets\n");
	str3 = (char*)malloc(sizeof(char) * 327);	
	printf("malloc str4 de 42 octets\n\n");
	str4 = (char*)malloc(sizeof(char) * 42);	

	printf("Allocated memory:\n");
	show_alloc_mem();
	printf("\nFull process memory\n");
	show_full_mem();

	printf("\nfree str\n");
	free(str);
	printf("Allocated memory:\n");
	show_alloc_mem();

	printf("\nfree str2\n");
	free(str2);
	printf("Allocated memory:\n");
	show_alloc_mem();

	printf("\nfree str3\n");
	free(str3);
	printf("Allocated memory:\n");
	show_alloc_mem();

	printf("\nfree str4\n");
	free(str4);
	printf("Allocated memory:\n");
	show_alloc_mem();
	printf("Full process memory\n");
	show_full_mem();

	printf("\nfree str4\n");
	free(str4);
}

int		main(int ac, char **av)
{

	(void)ac;
	if (av[1])
	{
		if (av[1][0] == '1')
		{
			printf("TEST_MALLOC\n");
			test_malloc();
		}
		else if (av[1][0] == '2')
		{
			printf("TEST_REALLOC\n");
			test_realloc();
		}
		else if (av[1][0] == '3')
		{
			printf("TEST_FREE\n");
			test_free();
		}
		else
			printf("please choose what test to do :\n1 -> malloc\n2 -> realloc\n3 -> free\n");
	}
	else
		printf("please choose what test to do :\n1 -> malloc\n2 -> realloc\n3 -> free\n");
	return (0);
}
