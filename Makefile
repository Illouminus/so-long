NAME = so_long
CC = gcc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror


LIBFT = ./libft/libft.a
PRINTF = ./printf/libftprintf.a
MLX_DIR = ./mlx/


SRCS = so_long.c init_map.c checkers/check_map.c checkers/check_walls.c checkers/check_game.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
MAKE_MLX = make -C $(MLX_DIR)

UNAME := $(shell uname)


ifeq ($(UNAME), Darwin) 
   INCLUDES = -I./includes -I./libft -I./printf -I/opt/X11/include
   MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
else
    INCLUDES = -I./includes -I./libft -I./printf -I./mlx
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
endif

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(MAKE_MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(PRINTF) $(MLX_FLAGS) $(INCLUDES)

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
	$(MAKE_MLX) clean

re: fclean all

.PHONY: all clean fclean re
