NAME = cub3d
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I ./include -I ./libft -I $(MLX_DIR) -g3 -fsanitize=address
MAKEFLAGS += --no-print-directory

RM = rm -f

SRC_SRC = main.c
PRS_SRC = check_args.c char_validation.c check_textures.c check_game.c
GME_SRC = images.c main_game.c movements.c pixels.c raycast.c

MLX_DIR         = ./minilibx-linux
MLX_MAKE        = Makefile
MLX_PATH        = ${MLX_DIR}/libmlx.a
MFLAGS          = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd


SRC = $(SRC_SRC) $(PRS_SRC) $(GME_SRC)

INCLUDES = ./include/cub3d.h ./libft/libft.h
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

SRC_DIR = ./src/
PRS_DIR = $(SRC_DIR)parser/
GME_DIR = $(SRC_DIR)game/
OBJ_DIR = ./obj/

OBJ_FILES = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# RULES
all: $(OBJ_DIR) $(LIBFT_DIR) $(NAME)

$(LIBFT): $(LIBFT_DIR)
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Objects for Main
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Objects for Parser
$(OBJ_DIR)%.o: $(PRS_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Objects for Game
$(OBJ_DIR)%.o: $(GME_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# basic library compiled
$(NAME): $(OBJ) $(LIBFT)
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1 
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJ) $(LIBFT) -o $(NAME) $(MFLAGS)
	@echo "$(GREEN)#### cub3d ####$(COLOR_OFF)"
	@echo "    -Has been compiled ✅"

# all .o files removed
clean:
	@$(RM) $(OBJ)
	@make clean -C libft
	@rm -rf $(OBJ_DIR)

# library .a file removed
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft
	@rm -rf $(OBJ_DIR)

re:	fclean all

.PHONY:	all clean fclean re
