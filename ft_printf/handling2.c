/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:21:20 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:21:22 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int	print_ptr(va_list args)
{
	void	*value;

	value = va_arg(args, void *);
	return (ft_putptr(value));
}
