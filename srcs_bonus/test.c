#include <stdio.h>

int	main(int argc, char **argv)
{
	int i = 0;
	char *str;

	printf("argc = %d \n", argc);
	while(argv[i])
	{
		printf("argv[%d] : %s \n", i, argv[i]);
		i++;
	}
	return (0);
}
