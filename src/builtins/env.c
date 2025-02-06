/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:06:34 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/21 15:06:34 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_special(char *key)
{
	char	*specials[1];
	size_t	i;

	specials[0] = "?";
	i = 0;
	while (i < 1)
	{
		ft_strcmp(specials[i], key);
		i++;
	}
	return (false);
}

int	builtin_env(t_cmd *cmd, t_env **envs)
{
	t_env	*env;

	(void)cmd;
	env = *envs;
	while (env)
	{
		if (!is_special(env->key) && env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
