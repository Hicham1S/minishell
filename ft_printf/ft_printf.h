/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:16:59 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:17:31 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"

int	print_int(va_list args);
int	print_string(va_list args);
int	print_chari(va_list args);
int	print_unsigned(va_list args);
int	print_ptr(va_list args);
int	print_hexa(va_list args, const char c);
int	ft_printf(const char *str, ...);

#endif
