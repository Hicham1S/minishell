#ifndef CMD_H
# define CMD_H

typedef struct s_env {
	char *val;
	struct s_env *next;
}	t_env;
typedef struct s_exp
{
	char	*val;
	struct	s_exp *next;
}	t_exp;

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"

// env.c
t_env	*create_env(char *txt);
void	add_env(t_env **head, t_env *new);
void	free_env(t_env **head);
t_env	*enlist_env(char **envp);
char *get_env_clone(char *name, t_env *head);

// exp.c
t_exp *create_exp(char *txt);
void add_exp(t_exp **head, t_exp *new);
void free_exp(t_exp **head);
void	swap_env(t_env *env1, t_env *env2);
t_env	*sort_env(t_env *env_clone);
t_exp	*env_to_exp(t_env *env_clone);


#endif