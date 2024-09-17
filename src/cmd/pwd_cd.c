#include "cmd.h"

int	pwd(t_env *env_clone)
{
	ft_printf("%s\n", get_env_clone("PWD", env_clone));
	return (0);
}