/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:32 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:13:33 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*getlonghexabase(void)
{
	char	*base;
	int		i;

	base = (char *)malloc(sizeof(char) * 17);
	i = 0;
	while (i < 10)
	{
		base[i] = '0' + i;
		i++;
	}
	while (i < 16)
	{
		base[i] = 'a' + i - 10;
		i++;
	}
	base[i] = '\0';
	return (base);
}

int	longhexalength(unsigned long long nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int	ft_putlonghexa(unsigned long long nb)
{
	char			*base;
	char			hex_digits[17];
	unsigned int	digit;
	int				i;
	int				count;

	i = 0;
	count = longhexalength(nb);
	base = getlonghexabase();
	while (nb > 0)
	{
		digit = nb % 16;
		hex_digits[i++] = base[digit];
		nb /= 16;
	}
	while (--i >= 0)
	{
		print_char(hex_digits[i]);
	}
	free(base);
	return (count);
}

int	ft_putptr(void *ptr)
{
	unsigned long long	address;
	int					count;

	address = (unsigned long long)ptr;
	count = 0;
	if (address == 0)
		count += ft_putstr("(nil)");
	else
	{
		write(1, "0x", 2);
		count += 2;
		count += ft_putlonghexa(address);
	}
	return (count);
}
