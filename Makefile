NAME		:= miniRT

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -O3 -std=c99
CPPFLAGS	:= -Iinclude -Ilib/mlx_linux -Ilib/libft
LDFLAGS		:= -Llib/libft -Llib/mlx_linux
LDLIBS		:= -lft -lmlx -lXext -lX11 -lm -lz

SRC_DIR		:= src
OBJ_DIR		:= obj
SRC			:= $(SRC_DIR)/main.c \
			   $(SRC_DIR)/color.c \
			   $(SRC_DIR)/engine/engine.c \
			   $(SRC_DIR)/engine/input/handle_key.c \
			   $(SRC_DIR)/engine/action/action.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx_get.c \
			   $(SRC_DIR)/graphicsctx/image.c \
			   $(SRC_DIR)/math/floating_point.c \
			   $(SRC_DIR)/math/quadratic.c \
			   $(SRC_DIR)/math/vec3_arithmetic.c \
			   $(SRC_DIR)/math/vec3_basis.c \
			   $(SRC_DIR)/math/vec3_metrics.c \
			   $(SRC_DIR)/math/vec3_products.c \
			   $(SRC_DIR)/loader/loader_rt.c \
			   $(SRC_DIR)/loader/parser_ambient.c \
			   $(SRC_DIR)/loader/parser_camera.c \
			   $(SRC_DIR)/loader/parser_color.c \
			   $(SRC_DIR)/loader/parser_light.c \
			   $(SRC_DIR)/loader/parser_shapes.c \
			   $(SRC_DIR)/loader/parser_utils.c \
			   $(SRC_DIR)/loader/parser_vec3.c \
			   $(SRC_DIR)/loader/get_next_line.c \
			   $(SRC_DIR)/loader/parser_double.c \
			   $(SRC_DIR)/loader/parser_int.c \
			   $(SRC_DIR)/renderer/renderer_intersection.c \
			   $(SRC_DIR)/renderer/renderer_intersection_cylinder.c \
			   $(SRC_DIR)/renderer/renderer_intersection_cylinder_utils.c \
			   $(SRC_DIR)/renderer/renderer_intersection_plane.c \
			   $(SRC_DIR)/renderer/renderer_intersection_sphere.c \
			   $(SRC_DIR)/renderer/renderer_ray.c \
			   $(SRC_DIR)/renderer/renderer_render.c \
			   $(SRC_DIR)/renderer/renderer_shade.c \
			   $(SRC_DIR)/scene/camera.c \
			   $(SRC_DIR)/scene/shapes_append.c \
			   $(SRC_DIR)/scene/scene.c
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:= lib/libft
MLX_DIR		:= lib/mlx_linux

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a:
	cd $(MLX_DIR) && sh ./configure

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	cd $(MLX_DIR) && sh ./configure clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	cd $(MLX_DIR) && sh ./configure clean

re: fclean all

.PHONY: all clean fclean re
