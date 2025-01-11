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

typedef struct s_token
{
	char		*txt;
	t_qtype		qtype;
	struct s_token	*next;
}	t_token;

#endif