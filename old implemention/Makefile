NAME = cub3d

FLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext

INCLUDES = -I$(MLX_DIR)

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(MLX_DIR)/minilibx.a $(NAME)

$(MLX_DIR)/minilibx.a:
	make -C $(MLX_DIR)

%.o: %.c
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) $(MLX) -lm $(INCLUDES) -o $(NAME)

clean:
	rm -rf $(OBJS)
	make -C $(MLX_DIR) clean

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
