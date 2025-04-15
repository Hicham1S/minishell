/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dawwad <dawwad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:52:12 by dawwad            #+#    #+#             */
/*   Updated: 2025/03/10 14:52:12 by dawwad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "tokens.h"

int	unmatched_quotes(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (c == 0 && is_quote(str[i]))
			c = str[i];
		else if (is_quote(c) && str[i] == c)
			c = 0;
		i++;
	}
	return (c);
}

t_token	*init_tokens(char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (str[i] != '\0')
		parse_token(&token, str, &i);
	return (token);
}
