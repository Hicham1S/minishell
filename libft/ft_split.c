/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:20:55 by dawwad            #+#    #+#             */
/*   Updated: 2024/06/19 18:20:56 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	checksep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

int	arrstrlen(const char *str, char sep)
{
	int	i;
	int	count;

	if (!*str)
		return (0);
	i = 0;
	count = 0;
	if (!(checksep(str[0], sep)))
		count++;
	while (str[i])
	{
		if ((checksep(str[i], sep))
			&& !(checksep(str[i + 1], sep)) && str[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	wordlen(const char *str, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (checksep(str[j], sep))
		j++;
	while (!(checksep(str[i + j], sep)) && str[i + j])
		i++;
	return (i);
}

char	*makeword(const char *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc((wordlen(str, sep) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (checksep(*str, sep))
		str++;
	while (!(checksep(str[i], sep)) && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *str, char sep)
{
	char	**arrstr;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	arrstr = (char **)malloc((arrstrlen(str, sep) + 1) * sizeof(char *));
	if (!arrstr)
		return (NULL);
	while (*str)
	{
		while (checksep(*str, sep) && *str)
			str++;
		if (*str)
		{
			arrstr[i] = makeword(str, sep);
			i++;
		}
		while (*str && !checksep(*str, sep))
			str++;
	}
	arrstr[i] = NULL;
	return (arrstr);
}
