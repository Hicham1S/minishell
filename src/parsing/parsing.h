#ifndef PARSING_H
# define PARSING_H

# include "../env/env.h"
# include "../libft/libft.h"
# include "../tokenization/tokens.h"
# include "../main/main.h"
# include <stdio.h>
# include <unistd.h>

char	*get_next_dollar(char *str, t_env *my_env, int start);
char	*append_text_before_dollar(char *res, char *txt, int *i);
char	*expand_env_var(char *res, char *txt, int *i, t_env *env);
void	handle_dollar(t_token *original, t_env *env);
void	do_handle_dollar(t_token *tokens, t_env *env);

void	merge_tokens(t_token *tokens);
void	finalize_tokens(t_token *tokens, t_env *env_clone);

#endif