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
		$(SRCDIR)/libft/ft_strjoin.c \
		$(SRCDIR)/libft/ft_substr.c \
		$(SRCDIR)/tokenization/tokens.c \
		$(SRCDIR)/tokenization/t_tokens.c \
		$(SRCDIR)/tokenization/quotation.c \
		$(SRCDIR)/cmd/env.c \
		$(SRCDIR)/cmd/exp.c \
		$(SRCDIR)/cmd/pwd.c\
		$(SRCDIR)/utils/ragequit.c \
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
	@mkdir -p $(OBJDIR)/$(dir $<) $(OBJDIR)/libft $(OBJDIR)/tokenization $(OBJDIR)/cmd $(OBJDIR)/utils $(OBJDIR)/main
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
