/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarraj <hsarraj@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:06:49 by hsarraj           #+#    #+#             */
/*   Updated: 2025/01/21 15:06:49 by hsarraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int handle_options(char **args, bool *n_option)
{
    size_t  i;
    size_t  j;

    *n_option = false;
    i = 1;
    while(args && args[i])
    {
        if(args[i][0] != '-')
            break;
        j = 1;
        while(args[i][j])
        {
            if(args[i][j] != 'n')
            {
                if(i == 1)
                    *n_option = false;
            return(i - 1);
            }
            *n_option = true;
            j++;
        }
        i++;
    }
    return (i - 1);
}

int builtin_echo(t_cmd *cmd, t_env **envs)
{
    bool    n_option;
    int     i;

    (void)envs;
    i = 1 + handle_options()
}