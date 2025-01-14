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
	char			*name;
	char			**args;
	int				infile;
	int				outfile;
	bool			has_heredoc;
	bool			has_pipe;
	pid_t			pid;
	struct s_cmd	*next;
}	t_cmd;


#endif