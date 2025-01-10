/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:09 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:16:50 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	handle_type(const char c, va_list args)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count += print_int(args);
	else if (c == 's')
		count += print_string(args);
	else if (c == 'c')
		count += print_chari(args);
	else if (c == 'u')
		count += print_unsigned(args);
	else if (c == 'x' || c == 'X')
		count += print_hexa(args, c);
	else if (c == 'p')
		count += print_ptr(args);
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	const char	*ptr;
	int			count;

	va_start(args, str);
	count = 0;
	ptr = str;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			if (*ptr)
				count += handle_type(*ptr, args);
			else
				break ;
		}
		else
			count += ft_putchar(*ptr);
		ptr++;
	}
	va_end(args);
	return (count);
}
