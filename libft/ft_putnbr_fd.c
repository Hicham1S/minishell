/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:26:34 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/19 18:26:36 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9 || n > 9)
		ft_putnbr_fd((n / 10), fd);
	if (n < 0)
	{
		if (n >= -9 && n <= 9)
			print_char('-', fd);
		print_char('0' - (n % 10), fd);
	}
	else
	{
		print_char('0' + (n % 10), fd);
	}
}
