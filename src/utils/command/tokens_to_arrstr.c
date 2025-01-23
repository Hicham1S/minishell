// #include "../../../includes/minishell.h"

// static size_t	get_arrstrlen(t_token *token)
// {
// 	size_t		i;
// 	t_token	*current;

// 	i = 0;
// 	current = token;
// 	while (current && ft_strcmp(current->txt, "") != 0)
// 	{
// 		i++;
// 		current = current->next;
// 	}
// 	return (i);
// }

// char	**tokens_to_arrstr(t_token *token)
// {
// 	size_t	i;
// 	size_t	len;
// 	t_token	*current;
// 	char	**tokens;

// 	i = 0;
// 	len = get_arrstrlen(token);
// 	tokens = (char **)malloc((len + 1) * sizeof(char *));
// 	current = token;
// 	while (i < len)
// 	{
// 		if (ft_strcmp(current->txt, "") != 0)
// 		{
// 			tokens[i] = ft_strdup(current->txt);
// 			i++;
// 		}
// 		current = current->next;
// 	}
// 	tokens[i] = NULL;
// 	return (tokens);
// }

// void	free_arrstr(char **arr)
// {
// 	size_t	i;

// 	if (!arr)
// 		return;
// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// }
