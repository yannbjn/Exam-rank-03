#include <unistd.h>
#include <stdarg.h>

void	prints(char *str, int *len)
{
	int	i = -1;
	if (!str)
		str = "(null)";
	while (str[++i])
		*len += write(1, &str[i], 1);
}

void	printdx(long long int nbr, int base, int *len)
{
	char *hex = "0123456789abcdef";
	
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		printdx((nbr / base), base, len);
	*len += write(1, &hex[nbr % base], 1);
}

int	ft_printf(const char *form, ...)
{
	int	len = 0;
	int	i = 0;
	
	va_list	args;
	va_start(args, form);

	while (form[i])
	{
		if (form[i] == '%')
		{
			i++;
			if (form[i] == 's')
				prints(va_arg(args, char *), &len);
			else if (form[i] == 'd')
				printdx((long long int)va_arg(args, int), 10, &len);
			else if (form[i] == 'x')
				printdx((long long int)va_arg(args, unsigned int), 16, &len);
		}
		else
			len += write(1, &form[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *str = "salut";
// 	int	i = -42;
// 	printf("%d : ", printf("string %s , d = %d , x = %x\n", str, i, i));
// 	ft_printf("%d : ", ft_printf("string %s , d = %d , x = %x\n", str, i, i));
// }