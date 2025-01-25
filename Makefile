# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRCDIR = src
UTILSDIR = $(SRCDIR)/utils
TOKENSDIR = $(UTILSDIR)/tokens
ENVDIR = $(UTILSDIR)/env
CMDDIR = $(UTILSDIR)/command
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
	  $(CMDDIR)/command_redirs.c

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
