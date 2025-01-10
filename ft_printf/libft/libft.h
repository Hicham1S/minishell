/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:13:53 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/24 19:14:59 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(char c);
int		ft_putstr(const char *str);
int		ft_putnbr(int nb);
int		ft_putunsigned(unsigned int nb);
int		ft_puthexa(unsigned int nb, const char c);
int		ft_putptr(void *ptr);
int		ft_putstri(const char *str);
void	print_char(const char c);

#endif
