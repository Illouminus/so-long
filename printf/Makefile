NAME = libftprintf.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDES = .

SRCS = ft_printf.c ft_print_pointer.c ft_putchar.c ft_putnbr_base.c ft_putnbr.c ft_putstr.c
OBJS = $(SRCS:.c=.o)
LIBC = ar rc
LIBR = ranlib

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re