#include "tokens.h"

char	*trim_str(char *mainstr, int i, int j)
{
	char	*val;
	int		k;

	k = 0;
	val = (char *)malloc((j - i + 1) * sizeof(char));
	if (!val)
		return (NULL);
	while (i < j)
		val[k++] = mainstr[i++];
	val[k] = '\0';
	return (val);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	handle_single_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	t_qtype	qtype;
	char	*substr;

	qtype = SINGLE;
	(*i)++;
	j = *i;
	while (str[j] && str[j] != '\'')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, qtype));
	free(substr);
	*i = j + 1;
}

void	handle_double_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	t_qtype	qtype;
	char	*substr;

	qtype = DOUBLE;
	(*i)++;
	j = *i;
	while (str[j] && str[j] != '\"')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, qtype));
	free(substr);
	*i = j + 1;
}

void	handle_no_quote(char *str, int *i, t_token **tokens)
{
	int		j;
	char	*substr;

	j = *i;
	while (str[j] && !is_space(str[j]) && str[j] != '\'' && str[j] != '\"')
		j++;
	substr = trim_str(str, *i, j);
	add_token(tokens, create_token(substr, NO));
	free(substr);
	*i = j;
}

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i] == '\'')
			handle_single_quote(str, &i, &tokens);
		else if (str[i] == '\"')
			handle_double_quote(str, &i, &tokens);
		else
			handle_no_quote(str, &i, &tokens);
	}
	return (tokens);
}

const char *qtype_to_string(t_qtype qtype)
{
	switch (qtype)
	{
		case NO:
			return "NO";
		case SINGLE:
			return "SINGLE";
		case DOUBLE:
			return "DOUBLE";
		default:
			return "UNKNOWN";
	}
}
