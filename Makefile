# ANSI color codes
RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
BLUE	:= \033[0;34m
MAGENTA	:= \033[0;35m
CYAN	:= \033[0;36m
RESET	:= \033[0m

NAME	:= cub3D
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g
RM		:= rm -rf

LIBFT_PATH  := ./libft
OBJ_PATH	:= ./obj
MAIN		:= main.c
SRC_FILES	:=

OBJS		:= $(patsubst %, $(OBJ_PATH)/%, $(SRC_FILES:.c=.o))
MAIN_OBJ	:= $(OBJ_PATH)/main.o

LIBFT		:= $(LIBFT_PATH)/libft.a

all: $(NAME)

submodule: git submodule update --init --recursive

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

.PHONY: all clean fclean re
