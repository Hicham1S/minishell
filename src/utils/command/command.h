#ifndef COMMAND_H
# define COMMAND_H

char	**init_args(t_token *token, int limit[2]);
void	cmd_redirs(t_env *envs, t_cmd *cmd, t_token *token, int limit[2]);
void	free_cmd(t_cmd *cmd);

#endif