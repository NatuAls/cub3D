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

# Core
SRCS = $(SRC_DIR)/core/main.c \
       $(SRC_DIR)/core/init.c \
       $(SRC_DIR)/core/init_map.c
# Render
SRCS += $(SRC_DIR)/render/render.c \
        $(SRC_DIR)/render/raycasting.c \
        $(SRC_DIR)/render/raycasting_dda.c \
        $(SRC_DIR)/render/draw.c \
        $(SRC_DIR)/render/draw_utils.c \
        $(SRC_DIR)/render/texture.c
# Input
SRCS += $(SRC_DIR)/input/events.c \
        $(SRC_DIR)/input/movement.c \
        $(SRC_DIR)/input/rotation.c
# Parser
SRCS += $(SRC_DIR)/parser/parser.c \
        $(SRC_DIR)/parser/parse_identifiers.c \
        $(SRC_DIR)/parser/parse_color.c \
        $(SRC_DIR)/parser/parse_map.c \
        $(SRC_DIR)/parser/parse_map_utils.c \
        $(SRC_DIR)/parser/validate_map.c \
        $(SRC_DIR)/parser/validate_map_utils.c
# Minimap
SRCS += $(SRC_DIR)/minimap/draw_minimap.c \
        $(SRC_DIR)/minimap/minimap_player.c \
        $(SRC_DIR)/minimap/minimap_tiles.c \
        $(SRC_DIR)/minimap/minimap_border.c \
        $(SRC_DIR)/minimap/minimap_line.c
# Utils
SRCS += $(SRC_DIR)/utils/utils.c \
        $(SRC_DIR)/utils/free.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(MLX) $(LIBFT) $(OBJS) $(INC_DIR)/cub3d.h Makefile
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
