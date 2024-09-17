#include"parsing.h"

char *expand_env_var(char *token, t_env *env_list)
{
    int i;
    int j;
    char *new_str;
    char *var_name;
    char *var_value;

    i = -1;

    while(token[++i])
    {
        if(token[i] == '$')
        {
            j = i + 1;
            while(ft_isalnum(token[j]) || token[j] == '_')
                j++;
            var_name = trim_str(str, i + 1, j);
            var_value = get_env_clone(var_name, env_list);
            free(var_name);
            if(var_value)
            {
                new_str = ft_strjoin
            }
        }
        i++;
    }

    return (token);
}
