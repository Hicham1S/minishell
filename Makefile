# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRCDIR = src
UTILSDIR = $(SRCDIR)/utils
TOKENSDIR = $(UTILSDIR)/tokens
ENVDIR = $(UTILSDIR)/env
EXECDIR = $(UTILSDIR)/exec
CMDDIR = $(UTILSDIR)/command
BUILTINDIR = $(SRCDIR)/builtins
LIBFTDIR = libft

# Libraries
LIBFT = $(LIBFTDIR)/libft.a
LIBS = -lreadline

# Source Files
SRC = $(TOKENSDIR)/replace_env.c \
      $(TOKENSDIR)/replace_env2.c \
      $(TOKENSDIR)/token_utils.c \
      $(TOKENSDIR)/token_init.c \
      $(TOKENSDIR)/token_management.c \
      $(TOKENSDIR)/token_parsing.c \
      $(TOKENSDIR)/redir_check.c \
      $(TOKENSDIR)/token_merge.c \
      $(ENVDIR)/env.c \
      $(ENVDIR)/env2.c \
	  $(CMDDIR)/command.c \
	  $(CMDDIR)/args.c \
	  $(CMDDIR)/command_redirs.c \
	  $(UTILSDIR)/main.c \
	  $(UTILSDIR)/debug.c \
	  $(UTILSDIR)/error.c \
	  $(UTILSDIR)/path.c \
	  $(UTILSDIR)/signal.c \
	  $(EXECDIR)/exec.c \
	  $(EXECDIR)/pipeline.c \
	  $(EXECDIR)/process.c \
	  $(EXECDIR)/redirs.c \
	  $(EXECDIR)/redirs2.c \
	  $(BUILTINDIR)/cd.c \
	  $(BUILTINDIR)/echo.c \
	  $(BUILTINDIR)/env.c \
	  $(BUILTINDIR)/exit.c \
	  $(BUILTINDIR)/export.c \
	  $(BUILTINDIR)/pwd.c \
	  $(BUILTINDIR)/unset.c

# Object Files
OBJ = $(SRC:.c=.o)

# Output Binary
NAME = minishell

# Rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

# Build libft if it doesn't exist
$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

# Clean Object Files
clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFTDIR) clean

# Clean Everything
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

# Rebuild Everything
re: fclean all

# Compile Individual Source Files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re
