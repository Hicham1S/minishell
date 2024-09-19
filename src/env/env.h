#ifndef ENV_H
# define ENV_H

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
# include "../ft_printf/ft_printf.h"
# include "../utils/utils.h"

// t_env
t_env	*create_env(char *txt);
void	add_env(t_env **head, t_env *new);
void	free_env(t_env **head);

// t_exp
t_exp *create_exp(char *txt);
void add_exp(t_exp **head, t_exp *new);
void free_exp(t_exp **head);

// build_exp.c
void	swap_env(t_env *env1, t_env *env2);
t_env	*sort_env(t_env *env_clone);
char	*add_double_quotes_to_str(char *str);
void	add_double_quotes(t_exp *head);
t_exp	*env_to_exp(t_env *env_clone);
t_exp	*env_to_exp(t_env *env_clone);

// env.c
t_env	*enlist_env(char **envp);
char	*get_env_clone(char *name, t_env *head);
int		env_exists(char *name, t_env *head);
int 	modify_env_clone(char *name, t_env *head, char *new);

// exp.c
void	new_exp(t_exp **head, char *txt);
char	*get_exp_clone(char *name, t_exp *head);
int		exp_exists(char *name, t_exp *head);
int		modify_exp_clone(char *name, t_exp *head, char *new);


// common_utils.c
char	*get_env_value(char *str);
char	*get_env_name(char *str);
int		check_env_exp(char *str);

// export_command.c
int	pre_equal(char c);
int *new_env_status(t_env *env_clone, t_exp *exp_clone, char *str);
int handle_export_errors(char *str);
int	register_env_exp(char *str ,t_env *env_clone, t_exp *exp_clone);

#endif