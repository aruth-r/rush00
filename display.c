# include <unistd.h>

void ft_putchar(char c);
void ft_putstr(char *str);
void error(void);
int *error_null(void);


void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return ;
}

void error(void)
{
	ft_putstr("Error\n");
}

int *error_null(void)
{
	error();
	return (NULL);
}
