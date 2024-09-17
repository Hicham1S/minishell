#include"parsing.h"

char *expand_env_var(char *token, t_env *env_list)
{
    int i;
    int j;
    char str;

    i = -1;

    while(token[++i])
    {
        if(token[i] == '$')
        {
            j = i;
            while(ft_isalnum(token[j]))
                j++;
            str = trim_str(str, i, j);
        }
        i++;
    }
    
    return (token);
}
