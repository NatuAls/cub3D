NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

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
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re