#include "parsing.h"

int	handle_builtins(char *arg)
{
	return (ft_strcmp(arg, "echo")
		|| ft_strcmp(arg, "exit")
		|| ft_strcmp(arg, "pwd")
		|| ft_strcmp(arg, "cd")
		|| ft_strcmp(arg, "unset")
		|| ft_strcmp(arg, "export")
		|| ft_strcmp(arg, "env"));
}

t_token2	*naming(t_token *tokens)
{
	
}