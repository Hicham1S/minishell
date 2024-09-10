/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:13:57 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:14:32 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunsigned_rec(unsigned int nb, int *count)
{
	if (nb > 9)
		ft_putunsigned_rec(nb / 10, count);
	print_char((const char)('0' + (nb % 10)));
	(*count)++;
}

int	ft_putunsigned(unsigned int nb)
{
	int	count;

	count = 0;
	ft_putunsigned_rec(nb, &count);
	return (count);
}
