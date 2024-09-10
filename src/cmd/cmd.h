#ifndef CMD_H
# define CMD_H

typedef struct s_env {
	char *val;
	struct s_env *next;
}	t_env;

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

t_env	*create_env(char *txt);
void	add_env(t_env **head, t_env *new);
void	free_env(t_env **head);
t_env	*enlist_env(char **envp);

#endif