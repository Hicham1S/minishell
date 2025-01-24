#include "../../../includes/minishell.h"
#include "tokens.h"

char	*process_env_string(t_env *env, t_token *token)
{
	char	*result;
	char	*temp;
	size_t	i;
	char	buff[2];
	result = NULL;
	i = 0;
	buff[1] = '\0';
	while (token->txt[i])
	{
		if (is_env_var_start(token, i))
		{
			temp = handle_env_var(env, token, &i);
			result = append_str(result, temp);
			free(temp);
		}
		else
		{
			buff[0] = token->txt[i++];
			result = append_str(result, buff);
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*replace_env(t_env *env, t_token *token)
{
	char	*new_str;
	char	*old_str;

	if (!token || !token->txt)
		return (NULL);
	new_str = process_env_string(env, token);
	if (!new_str)
		return (NULL);
	old_str = token->txt;
	token->txt = new_str;
	free(old_str);
	return (new_str);
}

void	replace_tokens_with_env(t_env *env, t_token *token)
{
	t_token	*current;

	if (!env || !token)
		return ;
	current = token;
	while (current)
	{
		if (current->txt && ft_strchr(current->txt, '$'))
			replace_env(env, current);
		if (ft_strcmp(current->txt, "<<") == 0)
			current = current->next->next;
		else
			current = current->next;
	}
}

static void	print_tokens(t_token *token)
{
	if (!token)
	{
		printf("no tokens inserted");
		return;
	}
	while (token)
	{
		if (token->txt)
			printf("Token: '%s', Type: %d\n", token->txt, token->qtype);
		token = token->next;
	}
}

// static void	print_arrstr(char **arr)
// {
// 	size_t	i;

// 	if (!arr)
// 	{
// 		printf("Array is NULL\n");
// 		return;
// 	}
// 	i = 0;
// 	while (arr[i])
// 	{
// 		printf("arr[%zu]: %s\n", i, arr[i]);
// 		i++;
// 	}
// 	if (i == 0)
// 		printf("Array is empty\n");
// }

void print_cmd(t_cmd *cmd)
{
	t_cmd *current = cmd;
	while (current)
	{
		printf("Command: \n");
		printf("Infile: %d\n", current->infile);
		printf("Outfile: %d\n", current->outfile);
		printf("Has Pipe: %d\n", current->has_pipe);
		printf("Has Heredoc: %d\n", current->has_heredoc);
		if (current->args)
		{
			int i = 0;
			while (current->args[i])
			{
				printf("Arg[%d]: %s\n", i, current->args[i]);
				i++;
			}
		}
		current = current->next;
	}
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *temp;

    while (cmd)
    {
        temp = cmd->next; // Save the pointer to the next node

        // Free arguments array
        if (cmd->args)
        {
            for (int i = 0; cmd->args[i] != NULL; i++)
                free(cmd->args[i]); // Free each argument string
            free(cmd->args);       // Free the array itself
            cmd->args = NULL;      // Avoid dangling pointers
        }

        // Close infile if valid and not a standard file descriptor
        if (cmd->infile > 2)
        {
            close(cmd->infile);
            cmd->infile = -1; // Mark as invalid after closing
        }

        // Close outfile if valid and not a standard file descriptor
        if (cmd->outfile > 2)
        {
            close(cmd->outfile);
            cmd->outfile = -1; // Mark as invalid after closing
        }

        free(cmd); // Free the current node
        cmd = temp; // Move to the next node
    }
}

int main(int argc, char **argv, char **envp)
{
	char    *input;
	t_token *tokens;
	t_env   *env;
	t_cmd   *cmd;
	
	(void)argc;
	(void)argv;
	env = init_env(envp);

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		if (unmatched_quotes(input))
		{
			printf("Error: Unmatched quotes\n");
			free(input);
			continue;
		}
		tokens = init_tokens(input);
		if (redir_check(tokens, env))
		{
			replace_tokens_with_env(env, tokens);
			printf("Parsed Tokens with Replaced Variables:\n");
			print_tokens(tokens);
			cmd = init_cmd(tokens);
			print_cmd(cmd);
			free_cmd(cmd);
		}
		if (tokens)
			free_tokens(&tokens);
		free(input);
	}
	free(env);
	return (0);
}

