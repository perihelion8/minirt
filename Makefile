NAME		:= miniRT
BONUS_NAME	:= miniRT_bonus

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -O3 -std=c99
CPPFLAGS	:= -Iinclude -Ilib/mlx_linux -Ilib/libft
LDFLAGS		:= -Llib/libft -Llib/mlx_linux
LDLIBS		:= -lft -lmlx -lXext -lX11 -lm -lz

SRC_DIR		:= src
OBJ_DIR		:= obj
SRC			:= $(SRC_DIR)/main.c \
			   $(SRC_DIR)/color.c \
			   $(SRC_DIR)/linkedlist/linkedlist.c \
			   $(SRC_DIR)/engine/engine.c \
			   $(SRC_DIR)/engine/engine_window.c \
			   $(SRC_DIR)/engine/engine_running.c \
			   $(SRC_DIR)/engine/input/handle_key.c \
			   $(SRC_DIR)/engine/action/action.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx_fullscreen.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx_resize.c \
			   $(SRC_DIR)/graphicsctx/graphicsctx_run.c \
			   $(SRC_DIR)/graphicsctx/image.c \
			   $(SRC_DIR)/math/floating_point.c \
			   $(SRC_DIR)/math/quadratic.c \
			   $(SRC_DIR)/math/vec3_arithmetic.c \
			   $(SRC_DIR)/math/vec3_basis.c \
			   $(SRC_DIR)/math/vec3_metrics.c \
			   $(SRC_DIR)/math/vec3_products.c \
			   $(SRC_DIR)/loader/loader_rt.c \
			   $(SRC_DIR)/loader/parser_ambient.c \
			   $(SRC_DIR)/loader/parser_line.c \
			   $(SRC_DIR)/loader/parser_camera.c \
			   $(SRC_DIR)/loader/parser_color.c \
			   $(SRC_DIR)/loader/parser_light.c \
			   $(SRC_DIR)/loader/parser_shapes.c \
			   $(SRC_DIR)/loader/parser_utils.c \
			   $(SRC_DIR)/loader/parser_vec3.c \
			   $(SRC_DIR)/loader/parser_double.c \
			   $(SRC_DIR)/loader/parser_ratio.c \
			   $(SRC_DIR)/loader/parser_int.c \
			   $(SRC_DIR)/loader/parser_error.c \
			   $(SRC_DIR)/loader/get_next_line.c \
			   $(SRC_DIR)/renderer/renderer_intersection.c \
			   $(SRC_DIR)/renderer/renderer_intersection_hit.c \
			   $(SRC_DIR)/renderer/renderer_intersection_cy.c \
			   $(SRC_DIR)/renderer/renderer_intersection_pl.c \
			   $(SRC_DIR)/renderer/renderer_intersection_sp.c \
			   $(SRC_DIR)/renderer/cylinder_transforms.c \
			   $(SRC_DIR)/renderer/renderer_ray.c \
			   $(SRC_DIR)/renderer/renderer_render.c \
			   $(SRC_DIR)/renderer/renderer_shade.c \
			   $(SRC_DIR)/scene/camera.c \
			   $(SRC_DIR)/scene/scene.c
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_SRC	:= $(filter-out $(SRC_DIR)/loader/parser_light.c \
			   $(SRC_DIR)/loader/parser_line.c \
			   $(SRC_DIR)/renderer/renderer_intersection.c,$(SRC)) \
			   $(SRC_DIR)/loader/parser_light_bonus.c \
			   $(SRC_DIR)/loader/parser_line_bonus.c \
			   $(SRC_DIR)/loader/parser_hyperboloid_bonus.c \
			   $(SRC_DIR)/renderer/renderer_intersection_bonus.c \
			   $(SRC_DIR)/renderer/renderer_hyperboloid_bonus.c
BONUS_OBJ	:= $(BONUS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS		:= $(wildcard include/*.h include/*/*.h src/*/*.h src/*/*/*.h)

LIBFT_DIR	:= lib/libft
MLX_DIR		:= lib/mlx_linux

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_DIR)/libmlx.a: $(wildcard $(MLX_DIR)/*.c $(MLX_DIR)/*.h)
	cd $(MLX_DIR) && sh ./configure

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(BONUS_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	cd $(MLX_DIR) && sh ./configure clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	cd $(MLX_DIR) && sh ./configure clean

re: fclean all

.PHONY: all clean fclean re bonus
