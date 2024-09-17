#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../cmd/cmd.h"
# include "../utils/utils.h"
# include "../tokenization/tokens.h"

typedef struct s_minishell
{
	t_token	*tokens;
	t_env	*our_env;
	t_exp	*our_exp;
}	t_minishell;

#endif