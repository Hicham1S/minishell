
#include"parsing.h"
#include "../libft/libft.h"

char *expand_env_var(char *token, t_env *env_list)
{
    int i;
    int j;
    char *new_str = NULL;
    char *var_name;
    char *var_value;

    i = -1;

    while(token[i])
    {
        if(token[i] == '$')
        {
            j = i + 1;
            while(ft_isalnum(token[j]) || token[j] == '_')
                j++;
            var_name = trim_str(token, i + 1, j);
            var_value = get_env_clone(var_name, env_list);
            free(var_name);
            if(var_value)
            {
                new_str = ft_strjoin(ft_substr(token, 0, i), var_value);
                new_str = ft_strjoin(new_str, &token[j]);
                free(token);
                token = new_str;
                i += ft_strlen(var_value)  -  1;
            }
            else
                i = j;
        }
        else
            i++;
    }
    return (token);
}
