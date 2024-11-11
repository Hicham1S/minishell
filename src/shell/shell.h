#ifndef SHELL_H
# define SHELL_H

# include <readline/history.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../env/env.h"
# include "../utils/utils.h"
# include "../tokenization/tokens.h"
# include "../parsing/parsing.h"
# include "../build_in_function/builtins.h"

typedef struct s_minishell
{
	t_token	*tokens;
	t_env	*our_env;
	t_exp	*our_exp;
}	t_minishell;

#endif