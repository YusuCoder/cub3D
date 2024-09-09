# ANSI color codes
RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
MAGENTA	:= \033[0;35m
CYAN	:= \033[0;36m
RESET	:= \033[0m

# Variables
NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Ofast -g
RM		:= rm -rf
LIBMLX	:= MLX42

# Include directories
INCLUDES	:= -I ./include -I ./lib/libft -I $(LIBMLX)/include
LIBS		:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Mandatory Source and Object files
OBJ_PATH	:= ./obj
MAIN		:= main.c
SRC_FILES	:=

OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

# Libft
LIBFT_PATH  := ./libft
LIBFT		:= $(LIBFT_PATH)/libft.a

# Headers
HEADER := include/cub3d.h

# Rules
all: submodule mlx $(LIBFT) $(NAME)

submodule:
	@git submodule update --init --recursive

mlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4 > /dev/null 2>&1
	@echo "$(GREEN)MLX42 connected.$(RESET)"

$(NAME): $(MAIN_OBJ) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline
	@echo "$(GREEN)cub3D created.$(RESET)"

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(P_SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@echo "$(MAGENTA)object files cleaned.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@echo "$(MAGENTA)cub3D removed.$(RESET)"

re: fclean all

.PHONY: all clean fclean re submodule mlx
