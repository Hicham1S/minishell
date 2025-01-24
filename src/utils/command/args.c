#include "../../../includes/minishell.h"
#include "command.h"

static size_t get_args_size(t_token *token, int limit[2])
{
    size_t  i = 0;
    t_token *current = token;
    int     j = 0;
    while (j < limit[0] && current)
    {
        current = current->next;
        j++;
    }
    while (current && j < limit[1])
    {
        if ((current->txt[0] == '>' || current->txt[0] == '<') 
            && current->qtype == NO)
        {
            if (current->next)
            {
                current = current->next->next;
                j += 2;
            }
            continue;
        }
        if (ft_strcmp(current->txt, "") == 0)
        {
            current = current->next;
            j++;
            continue;
        }
        i++;
        current = current->next;
        j++;
    }
    return (i);
}

static char **fill_args(t_token *token, int limit[2], char **arrstr)
{
    t_token *current = token;
    int     i = 0;
    int     j = 0;

    while (j < limit[0] && current)
    {
        current = current->next;
        j++;
    }
    while (current && j < limit[1])
    {
        if ((current->txt[0] == '>' || current->txt[0] == '<') 
            && current->qtype == NO)
        {
            if (current->next)
            {
                current = current->next->next;
                j += 2;
            }
            continue;
        }
        if (ft_strcmp(current->txt, "") == 0)
        {
            current = current->next;
            j++;
            continue;
        }
        arrstr[i++] = ft_strdup(current->txt);
        current = current->next;
        j++;
    }
    arrstr[i] = NULL;
    return (arrstr);
}

char **init_args(t_token *token, int limit[2])
{
    char    **arrstr;
    size_t  size;
    
    size = get_args_size(token, limit);
    arrstr = (char **)malloc((size + 1) * sizeof(char *));
    if (!arrstr)
        return (NULL);
    
    return (fill_args(token, limit, arrstr));
}