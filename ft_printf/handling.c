/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:19:42 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:20:58 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	print_int(va_list args)
{
	int	value;

	value = va_arg(args, int);
	return (ft_putnbr(value));
}

int	print_string(va_list args)
{
	char	*value;

	value = va_arg(args, char *);
	return (ft_putstr(value));
}

int	print_chari(va_list args)
{
	int	value;

	value = va_arg(args, int);
	ft_putchar(value);
	return (1);
}

int	print_unsigned(va_list args)
{
	unsigned int	value;

	value = va_arg(args, unsigned int);
	return (ft_putunsigned(value));
}

int	print_hexa(va_list args, const char c)
{
	unsigned int	value;

	value = va_arg(args, unsigned int);
	return (ft_puthexa(value, c));
}
