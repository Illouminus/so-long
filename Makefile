NAME = so_long
CC = gcc
RM = rm -f
CFLAGS = 
INCLUDES = -I./includes -I./libft -I./mlx -I./printf

LIBFT = ./libft/libft.a
PRINTF = ./printf/libftprintf.a

SRCS = so_long.c init_map.c checkers/check_map.c checkers/check_walls.c checkers/check_game.c gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(PRINTF) $(INCLUDES)

$(LIBFT):
	make -C ./libft

$(PRINTF):
	make -C ./printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(RM) $(OBJS)
	make -C ./printf clean
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./printf fclean
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
