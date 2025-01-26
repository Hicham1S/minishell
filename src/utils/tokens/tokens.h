#ifndef TOKENS_H
# define TOKENS_H

//token_utils
int		is_space(char c);
int		is_redir(char c);
int		is_quote(char c);
int		is_alphanumu(char c);

// Token management
void	add_token(t_token **token, char *txt, t_qtype qtype, int flag);
void	free_tokens(t_token **tokens);
void	free_one_token(t_token *token);
void	remove_head(t_token **token);
void	cleanup_tokens(t_token **token);

// Token parsing
int		single_quotes(t_token **token, char *str, int *i);
int		double_quotes(t_token **token, char *str, int *i);
int		no_quotes(t_token **token, char *str, int *i);
int		redir_token(t_token **token, char *str, int *i);
void	parse_token(t_token **token, char *str, int *i);
int		unmatched_quotes(char *str);

// Replace env
char	*append_str(char *str, const char *append);
int		is_env_var_start(t_token *token, size_t i);
char	*handle_env_var(t_env *env, t_token *token,
			size_t *i);

// Redir check
int		redir_check(t_token *token, t_env *env);

// Token merge
void	merge_tokens(t_token **token);

#endif