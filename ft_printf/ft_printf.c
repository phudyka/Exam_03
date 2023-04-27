#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int	ft_printstr(char *str)
{
	int i = 0;

	if (!str)
		return(write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnbr(long long int nbr, int base)
{
	int		len = 0;
	char	*hex = "0123456789abcdef";

	if (nbr < 0)
	{
		nbr *= -1;
		len += write(1, "-", 1);
	}
	if (nbr >= base)
		len += ft_printnbr((nbr / base), base);
	len += write(1, &hex[nbr % base], 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int	i = 0;
	int	len = 0;
	va_list	arg;
	
	va_start(arg, format);
	while (format[i])
	{
		if ((format[i] == '%') && (format[i + 1]))
		{
			i++;
			if (format[i] == 's')
				len += ft_printstr(va_arg(arg, char *));
			else if (format[i] == 'd')
				len += ft_printnbr((long long int)va_arg(arg, int), 10);
			else if (format[i] == 'x')
				len += ft_printnbr((long long int)va_arg(arg, unsigned int), 16);
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(arg);
	return (len);
}
