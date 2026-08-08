NAME = miniRT

CC = cc
CFLAGS = -Wextra -Werror -Wall -O2
RM = rm -rf

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	MLX_SRC = ./lib/minilibx_opengl_20191021
	MLX_FLAGS = -framework OpenGL -framework AppKit
else
	MLX_SRC = ./lib/minilibx-linux
	MLX_FLAGS = -Llib/minilibx -lmlx -lXext -lX11 -lm -lz
endif

MLX_DIR = ./lib/minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDE = -I ./include -I ./lib/minilibx
SRC = ./src/geometry/cone.c \
	  ./src/geometry/cone2.c \
	  ./src/geometry/cyl.c \
	  ./src/geometry/cyl2.c \
	  ./src/geometry/material.c \
	  ./src/geometry/plane.c \
	  ./src/geometry/rgb.c \
	  ./src/geometry/rgb2.c \
	  ./src/geometry/shape.c \
	  ./src/geometry/sphere.c \
	  ./src/types/ambient_light.c \
	  ./src/types/camera.c \
	  ./src/types/comps.c \
	  ./src/types/conf.c \
	  ./src/types/light.c \
	  ./src/types/ray.c \
	  ./src/types/renderer.c \
	  ./src/types/renderer2.c \
	  ./src/types/xs.c \
	  ./src/main.c \
	  ./src/math_helper.c \
	  ./src/parse_helper.c \
	  ./src/str_helper.c

OBJ = $(SRC:.c=.o)

LIB_ARCHIVES = ./lib/datastructures/datastructures.a \
			   ./lib/gc/gc.a \
			   ./lib/gc_libft/gc_libft.a \
			   ./lib/libft/libft.a \
			   ./lib/tuple/tuple.a

all: $(NAME)

$(MLX):
	@cp -R $(MLX_SRC) $(MLX_DIR)
	@make -C $(MLX_DIR)

$(LIB_ARCHIVES):
	@make -C $(dir $@)

$(NAME): $(MLX) $(LIB_ARCHIVES) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB_ARCHIVES) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "Created $(NAME)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@for dir in $(dir $(LIB_ARCHIVES)); do make -C $$dir fclean; done
	@$(RM) $(OBJ)
	@$(RM) $(MLX_DIR)
	@echo "Removed *.o in $(NAME)"

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed $(NAME)"

bonus: $(NAME)
	@echo "Created $(NAME) with bonus"

re: fclean all

.PHONY: all clean fclean re bonus
