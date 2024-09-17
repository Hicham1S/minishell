#ifndef TOKENS_H
# define TOKENS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../cmd/cmd.h"

typedef enum e_qtype
{
	DOUBLE,
	SINGLE,
	NO
}	t_qtype;

typedef struct s_token
{
	char			*txt;
	t_qtype			qtype;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_minishell
{
	t_token	*tokens;
	t_env	*our_env;
	t_exp	*our_exp;
}	t_minishell;

// quotation.c
int		check_quotation(char *str);

// tokens.c
t_token	*create_token(char *txt, t_qtype qtype);
void	add_token(t_token **head, t_token *new);
void	free_tokens(t_token **head);
char	*trim_str(char *mainstr, int i, int j);
void	enlist_tokens_helper(char *str, int *i, t_token **tokens, char quote);
t_token	*enlist_tokens(char *str);

#endif
