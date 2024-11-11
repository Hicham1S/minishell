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
		$(SRCDIR)/libft/ft_strcmp.c \
		$(SRCDIR)/libft/ft_strlcat.c \
		$(SRCDIR)/libft/ft_strjoin.c \
		$(SRCDIR)/libft/ft_substr.c \
		$(SRCDIR)/libft/ft_isalnum.c \
		$(SRCDIR)/libft/ft_memset.c \
		$(SRCDIR)/libft/ft_itoa.c \
		$(SRCDIR)/tokenization/tokens.c \
		$(SRCDIR)/tokenization/t_tokens.c \
		$(SRCDIR)/tokenization/quotation.c \
		$(SRCDIR)/env/build_exp.c \
		$(SRCDIR)/env/common_utils.c \
		$(SRCDIR)/env/env.c \
		$(SRCDIR)/env/exp.c \
		$(SRCDIR)/env/export_command.c \
		$(SRCDIR)/env/unset_command.c \
		$(SRCDIR)/env/t_env.c \
		$(SRCDIR)/env/t_exp.c \
		$(SRCDIR)/utils/ragequit.c \
		$(SRCDIR)/parsing/dollar.c \
		$(SRCDIR)/parsing/merge.c \
		$(SRCDIR)/parsing/separation.c \
		$(SRCDIR)/build_in_function/pwd_cd.c \
		$(SRCDIR)/main/init_shell.c \
		$(SRCDIR)/main/main.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Library
LIBS = $(LIBDIR)/libftprintf.a

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)/$(dir $<) $(OBJDIR)/libft $(OBJDIR)/tokenization $(OBJDIR)/env $(OBJDIR)/utils $(OBJDIR)/main $(OBJDIR)/build_in_function $(OBJDIR)/parsing2 $(OBJDIR)/shell
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
