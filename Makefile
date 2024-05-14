NAME = so_long
CC = cc -g
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g


LIBFT = ./libft/libft.a
PRINTF = ./printf/libftprintf.a
MLX_DIR = ./mlx/


SRCS = so_long.c init_map.c checkers/check_map.c checkers/check_walls.c checkers/check_route.c\
		 checkers/check_game.c mlx_outils/mlx_outils.c mlx_outils/layer/layer_outils.c \
		 mlx_outils/layer/player_draw.c mlx_outils/layer/enemy_draw.c mlx_outils/layer/sheep_draw.c  \
		 mlx_outils/image_outils.c  mlx_outils/player_outils.c \
		 mlx_outils/upload_sprites.c  mlx_outils/keys_outils.c \
		 outils/map_outils.c outils/free_player.c outils/free_resources.c outils/init_main.c outils/map_count.c \
		 mlx_outils/sheep/sheep_count.c mlx_outils/sheep/sheep_outils.c \
		 mlx_outils/enemy/init_enemy_pos.c mlx_outils/enemy/enemy_outils.c mlx_outils/enemy/enemy_update.c\
		 gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)
MAKE_MLX = make -C $(MLX_DIR)

UNAME := $(shell uname)


ifeq ($(UNAME), Darwin) 
   INCLUDES = -I./includes -I./libft -I./printf -I./mlx
   MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
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
