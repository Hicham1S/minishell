NAME = Minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRCDIR = src
OBJDIR = obj
LIBDIR = $(SRCDIR)/ft_printf

# Source files
SRCS =	$(SRCDIR)/libft/ft_strdup.c \
		$(SRCDIR)/libft/ft_strlcpy.c \
		$(SRCDIR)/libft/ft_strlen.c \
		$(SRCDIR)/libft/ft_strncmp.c \
		$(SRCDIR)/tokenization/tokens.c \
		$(SRCDIR)/tokenization/t_tokens.c \
		$(SRCDIR)/tokenization/quotation.c \
		$(SRCDIR)/cmd/env.c 

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Library
LIBS = $(LIBDIR)/libftprintf.a

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)/$(dir $<) $(OBJDIR)/libft $(OBJDIR)/tokenization $(OBJDIR)/cmd
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
