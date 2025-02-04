#ifndef TYPES_H
# define  TYPES_H

# include <sys/types.h>
# include <stdbool.h>

typedef enum	e_qtype
{
	NO,
	SINGLE,
	DOUBLE
}	t_qtype;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**args;
	int				infile;
	int				outfile;
	int				has_heredoc;
	int				has_pipe;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_token
{
	char		*txt;
	t_qtype		qtype;
	int			merge_next;
	struct s_token	*next;
}	t_token;

t_env	*get_env(t_env *env, char *key);
void	set_env(t_env **env, char *key, char *value);
t_env	*init_env(char **envp);
void	free_env(t_env *env);
void	del_env(t_env **env, char *key);
void	replace_tokens_with_env(t_env *env, t_token *token);
char	**format_env(t_env *env);


t_token *init_tokens(char *str);
void	free_tokens(t_token **tokens);
void	cleanup_tokens(t_token **token);
int		is_redir_token(t_token *token, char *to_compare);

char	**tokens_to_arrstr(t_token *token);
void	free_arrstr(char **arr);

t_cmd	*init_cmd(t_token *token);

#endif