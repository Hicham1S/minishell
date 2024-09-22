#include "parsing.h"
#include "../libft/libft.h"

char *expand_pid(char *token, int i)
{
	char *new_str = NULL;
	char *temp;
	pid_t pid;
	char *pid_str;
	int dollar_count = 0;

	pid = getpid();
	pid_str = ft_itoa(pid);

    while (token[i + dollar_count] == '$')
        dollar_count++;

    if (dollar_count > 1)
    {
        char *sub_str = ft_substr(token, 0, i);
        new_str = ft_strjoin(sub_str, pid_str);
        free(sub_str);

        while (dollar_count > 2)
        {
            temp = ft_strjoin(new_str, pid_str);
            free(new_str);
            new_str = temp;
            dollar_count -= 2;
        }

        temp = ft_strjoin(new_str, &token[i + dollar_count]);
        free(new_str);
        free(token);
        token = temp;
    }

    free(pid_str);
    return token;
}

char *expand_exit_status(char *token, int i, int last_exit_status)
{
    char *new_str;
    char *status_str;
    char *temp;

    status_str = ft_itoa(last_exit_status);

    char *sub_str = ft_substr(token, 0, i);
    new_str = ft_strjoin(sub_str, status_str);
    free(sub_str);

    temp = ft_strjoin(new_str, &token[i + 2]);
    free(new_str);
    free(status_str);
    free(token);
    token = temp;

    return token;
}
char *handle_literal_dollar(char *token, int i)
{
    char *new_str;
    char *sub_str;

    sub_str = ft_substr(token, 0, i);
    new_str = ft_strjoin(sub_str, &token[i + 1]);
    free(sub_str);
    free(token);
    return new_str;
}

char *handle_invalid_variable(char *token, int *i)
{
    (*i)++;

    while (token[*i] && (ft_isdigit(token[*i]) || (!ft_isalnum(token[*i]) && token[*i] != '_')))
        (*i)++;

    return token;
}

char *expand_env_var(char *token, t_env *env_list, int last_exit_status)
{
    int i = 0;
    int j;
    char *new_str = NULL;
    char *var_name;
    char *var_value;
    char *temp;

    while (token[i])
    {
        if (token[i] == '\\' && token[i + 1] == '$')
        {
            token = handle_literal_dollar(token, i);
            i++;
        }
        else if (token[i] == '$')
        {
            if (token[i + 1] == '$')
            {
                token = expand_pid(token, i);
                i += ft_strlen(ft_itoa(getpid())) - 1;
            }
            else if (token[i + 1] == '?')
            {
                token = expand_exit_status(token, i, last_exit_status);
                i += ft_strlen(ft_itoa(last_exit_status)) - 1;
            }
            else if (ft_isdigit(token[i + 1]) || (!ft_isalnum(token[i + 1]) && token[i + 1] != '_'))
            {
                token = handle_invalid_variable(token, &i);
            }
            else
            {
                j = i + 1;
                while (ft_isalnum(token[j]) || token[j] == '_')
                    j++;

                var_name = trim_str(token, i + 1, j);
                var_value = get_env_clone(var_name, env_list);
                free(var_name);

                if (var_value)
                {
                    char *sub_str = ft_substr(token, 0, i);
                    new_str = ft_strjoin(sub_str, var_value);
                    free(sub_str);

                    temp = ft_strjoin(new_str, &token[j]);
                    free(new_str);
                    free(token);
                    token = temp;
                    i += ft_strlen(var_value) - 1;
                }
                else
                    i = j;
            }
        }
        else
        {
            i++;
        }
    }
    return token;
}
