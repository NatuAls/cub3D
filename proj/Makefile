NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/init.c \
       $(SRC_DIR)/init_map.c \
       $(SRC_DIR)/render.c \
       $(SRC_DIR)/raycasting.c \
       $(SRC_DIR)/raycasting_dda.c \
       $(SRC_DIR)/draw.c \
       $(SRC_DIR)/events.c \
       $(SRC_DIR)/movement.c \
       $(SRC_DIR)/rotation.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/parse_identifiers.c \
       $(SRC_DIR)/parse_color.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
