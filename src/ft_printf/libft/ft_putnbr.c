/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:14:06 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:07:17 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_rec(int nb, int *count)
{
	if (nb < -9 || nb > 9)
		ft_putnbr_rec(nb / 10, count);
	if (nb < 0)
	{
		if (nb > -10)
		{
			print_char('-');
			(*count)++;
		}
		print_char('0' - (nb % 10));
	}
	else
		print_char('0' + (nb % 10));
	(*count)++;
}

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
	{
		print_char('0');
		return (1);
	}
	ft_putnbr_rec(nb, &count);
	return (count);
}
