#include "env.h"

char	*get_env_value(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (ft_substr(str, i + 1, ft_strlen(str) - i - 1));
	return (NULL);
}

char	*get_env_name(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

int	check_env_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!pre_equal(str[i]))
			return (0);
		i++;
	}
	return (1);
}