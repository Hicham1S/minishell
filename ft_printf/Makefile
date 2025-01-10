CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c handling.c handling2.c libft/ft_putunsigned.c libft/ft_putstr.c libft/ft_putptr.c libft/ft_putnbr.c libft/ft_puthexa.c libft/ft_putchar.c libft/print_char.c
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(BONUS_OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
