# ANSI color codes
RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
MAGENTA	:= \033[0;35m
CYAN	:= \033[0;36m
RESET	:= \033[0m

# Variables
NAME	:= cub3d
BONUS	:= cub3d_bonus
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Ofast -g

RM		:= rm -rf
LIBMLX	:= ./mlx_lib

# Include directories
INCLUDES	:= -I ./include -I ./libft -I $(LIBMLX)/include
# LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

#for macOS
MLX42FLAGS		:= -lglfw -framework Cocoa -framework OpenGL -framework IOKit

#for Ubuntu:
# MLX42FLAGS		:= -lglfw -ldl -lGL

LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl $(MLX42FLAGS) -pthread -lm

# Mandatory Source and Object files
OBJ_PATH	:= ./obj
SRC_PATH	:= ./src
SRC_FILES	:= main.c \
				./parse/parse.c \
				./parse/errors.c \
				./parse/copy_validate_map.c \
				./parse/get_next_line.c \
				./parse/get_next_line_utils.c \
				./parse/extracting.c \
				./parse/map_data.c \
				./parse/extract_map.c \
				./parse/check_components.c \
				./parse/get_player_dir.c \
				./parse/middle_wals.c \
				./parse/sizeof_lines.c \
				./parse/filter_map.c \
				./parse/set_path.c \
				./parse/utils.c \
				./parse/cp_color.c \
				initializing.c \
				simulation.c \
				event_hooks.c \
				ray_casting.c \
				rendering.c \
				utils.c \
				free.c \
				error.c \
				movement.c

# Bonus Source and Object files
BONUS_OBJ_PATH	:= ./obj_bonus
BONUS_SRC_PATH	:= ./src_bonus
BONUS_SRC		:= main_bonus.c \
				./parse/bonus_parse.c \
				./parse/bonus_errors.c \
				./parse/bonus_copy_validate_map.c \
				./parse/get_next_line.c \
				./parse/get_next_line_utils.c \
				./parse/bonus_extracting.c \
				./parse/bonus_map_data.c \
				./parse/bonus_extract_map.c \
				./parse/bonus_check_components.c \
				./parse/bonus_get_player_dir.c \
				./sound_handling/play_sound.c \
				./sound_handling/utils.c \
				./parse/bonus_sizeof_lines.c \
				./parse/bonus_middle_wals.c \
				./parse/bonus_filter_map.c \
				./parse/bonus_set_path.c \
				./parse/bonus_utils.c \
				./parse/bonus_cp_color.c \
				initializing_bonus/init_data_bonus.c \
				initializing_bonus/init_map_bonus.c \
				initializing_bonus/init_player_bonus.c \
				initializing_bonus/init_texture_bonus.c \
				initializing_bonus/init_sprites_bonus.c \
				simulation_bonus.c \
				hooks_bonus.c \
				ray_casting_bonus.c \
				ray_casting_utils_bonus.c \
				rendering_bonus.c \
				utils_bonus.c \
				free_bonus.c \
				error_bonus.c \
				minimap_bonus.c \
				sprite_bonus.c \
				weapon_bonus.c \
				weapon_utils_bonus.c \
				movement_handler_bonus.c \
				movement_utils.c

# Add paths to object files
OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
BONUS_OBJS	:= $(patsubst %, $(BONUS_OBJ_PATH)/%, $(BONUS_SRC:.c=.o))

# Libft
LIBFT_PATH	:= ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a

# Headers
HEADER 			:= include/cub3d.h
HEADER_BONUS	:= include/cub3d_bonus.h

# Rules
all: submodule mlx $(LIBFT) $(NAME)

submodule:
	@git submodule update --init --recursive > /dev/null 2>&1

mlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1
	@echo "$(GREEN)MLX42 connected.$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LIBS)
	@echo "$(GREEN)cub3D created.$(RESET)"

# $(NAME): $(OBJS) $(LIBFT)
# 	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
# 	@echo "$(GREEN)cub3D created.$(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_PATH)/%.o: $(BONUS_SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

bonus: submodule mlx $(LIBFT) $(BONUS)

$(BONUS): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
	@echo "$(YELLOW)cub3D_bonus created.$(RESET)"

clean:
	@$(RM) $(OBJ_PATH) $(BONUS_OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "$(MAGENTA)object files cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@$(RM) $(LIBMLX)/build
	@echo "$(MAGENTA)executable files removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus submodule mlx


# /*        XXXXXX       XXXXXXXXXXX   */
# /*       XXXXXXX      XXXXXXXXXXXXX  */
# /*      XXXXXXXX     XXX         XXX */
# /*     XXX   XXX     XXX         XXX */
# /*    XXX    XXX               XXXX  */
# /*   XXX     XXX             XXXX    */
# /*  XXX      XXX           XXXX      */
# /* XXX       XXX         XXXX        */
# /* XXXXXXXXXXXXXXXX    XXXX          */
# /* XXXXXXXXXXXXXXXX  XXXX            */
# /*           XXX     XXX             */
# /*           XXX     XXXXXXXXXXXXXXX */
# /*           XXX     XXXXXXXXXXXXXXX */
