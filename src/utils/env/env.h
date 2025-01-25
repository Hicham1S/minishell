#ifndef ENV_H
# define ENV_H

t_env	*get_env(t_env *env, char *key);
t_env	*new_env(char *key, char *value);
void	set_env(t_env **env, char *key, char *value);
void	free_env(t_env *env);
void	free_one_env(t_env *env);

#endif