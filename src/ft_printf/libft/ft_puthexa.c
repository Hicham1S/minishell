/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:01:36 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:03:18 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_toupper(char *x)
{
	int	i;

	i = 0;
	while (x[i])
	{
		if (x[i] >= 'a' && x[i] <= 'z')
			x[i] -= 32;
		i++;
	}
	return (x);
}

char	*gethexabase(const char c)
{
	char	*base;
	int		i;

	i = 0;
	base = (char *)malloc(sizeof(char) * 17);
	while (i < 10)
	{
		base[i] = '0' + i;
		i++;
	}
	while (i < 16)
	{
		base[i] = 'a' + (i - 10);
		i++;
	}
	base[i] = '\0';
	if (c == 'X')
		ft_toupper(base);
	return (base);
}

int	hexalength(unsigned int nb)
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

int	ft_puthexa(unsigned int nb, const char c)
{
	char			*base;
	char			hex_digits[8];
	unsigned int	digit;
	int				i;
	int				count;

	i = 0;
	count = hexalength(nb);
	base = gethexabase(c);
	if (nb == 0)
		print_char('0');
	while (nb > 0)
	{
		digit = nb % 16;
		hex_digits[i++] = base[digit];
		nb /= 16;
	}
	i = i - 1;
	while (i >= 0)
	{
		print_char(hex_digits[i]);
		i--;
	}
	free(base);
	return (count);
}
