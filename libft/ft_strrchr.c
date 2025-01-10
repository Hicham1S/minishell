/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:20:21 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/13 14:20:23 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	i = 0;
	uc = (unsigned char)c;
	while (s[i] != '\0')
		i++;
	if (c == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		if (s[i - 1] == uc)
			return ((char *)(s + (i - 1)));
		i--;
	}
	return (NULL);
}
