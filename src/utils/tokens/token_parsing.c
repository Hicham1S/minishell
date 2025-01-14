#include "../../../includes/minishell.h"
#include "tokens.h"


int double_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;
	
	if (str[*i] == '\"')
	{
		(*i)++;
		j = *i;
		while (str[j] != '\"' && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (0);
		sub = ft_substr(str, *i, j - *i);
		if (!sub)
			return (0);
		add_token(token, sub, DOUBLE);
		free(sub);
		*i = j + 1;
		return (1);
	}
	return (0);
}

int single_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;
	
	if (str[*i] == '\'')
	{
		(*i)++;
		j = *i;
		while (str[j] != '\'' && str[j] != '\0')
			j++;
		if (str[j] == '\0')
			return (0);
		sub = ft_substr(str, *i, j - *i);
		if (!sub)
			return (0);
		add_token(token, sub, SINGLE);
		free(sub);
		*i = j + 1;
		return (1);
	}
	return (0);
}

int no_quotes(t_token **token, char *str, int *i)
{
	int     j;
	char    *sub;

	while (is_space(str[*i]))
		(*i)++;
	j = *i;
	while (str[*i] && !is_quote(str[*i])
		&& !is_space(str[*i]) && !is_redir(str[*i]))
		(*i)++;
	if (*i > j)
	{
		sub = ft_substr(str, j, *i - j);
		if (sub)
		{
			add_token(token, sub, NO);
			free(sub);
		}
	}
	return (1);
}

int	redir_token(t_token **token, char *str, int *i)
{
	char	*sub;

	if (is_redir(str[*i]))
	{
		if (str[*i] == str[*i + 1])
		{
			sub = ft_substr(str, *i, 2);
			add_token(token, sub, NO);
			free(sub);
			*i += 2;
		}
		else
		{
			sub = ft_substr(str, *i, 1);
			add_token(token, sub, NO);
			free(sub);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

void parse_token(t_token **token, char *str, int *i)
{
	if (is_quote(str[*i]) == 1)
	{
		if (!single_quotes(token, str, i))
			return;
	}
	else if (is_quote(str[*i]) == 2)
	{
		if (!double_quotes(token, str, i))
			return;
	}
	else if (is_redir(str[*i]))
	{
		if (!redir_token(token, str, i))
			return;
	}
	else if (!is_space(str[*i]))
	{
		if (!no_quotes(token, str, i))
			return;
	}
	else
		(*i)++;
}