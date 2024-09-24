SRC =  ft_error.c ft_bzero.c ft_isalpha.c ft_isdigit.c ft_memcpy.c ft_memset.c ft_strlcat.c ft_strlen.c ft_strrchr.c ft_toupper.c ft_isalnum.o ft_isascii.o ft_isprint.o ft_memmove.o ft_strchr.o ft_strlcpy.o ft_strncmp.o ft_tolower.o ft_memchr.o ft_memcmp.o ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o ft_strjoin.o ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_c.o ft_d-i.o ft_p.o ft_printf.o ft_s.o ft_u.o ft_x-X.o get_next_line.o get_next_line_utils.o ft_strisnum.c free_matrix.c get_matrix_size.c ft_fstrjoin.c
BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)
C = gcc -c
FLAGS = -Wall -Wextra -Werror -g3
NAME = libft.a
RM =  /bin/rm -f

TOTAL_FILES = $(words $(SRC))
CURRENT_FILES = 0
COLORS = 31 32 33 34 35 36 37

define print_progress
	$(eval CURRENT_FILES=$(shell echo $$(($(CURRENT_FILES)+1))))
	$(eval PERCENT=$(shell echo $$(( ($(CURRENT_FILES) * 100) / $(TOTAL_FILES) ))))
	$(eval COLOR=$(shell echo $(COLORS) | cut -d " " -f $$(($(CURRENT_FILES) % 7 + 1))))
	@printf "\rCompiling: [\033[$(COLOR)m$(notdir $<)\033[0m] $(PERCENT)%%"
endef

%.o: %.c
	@$(C) $(FLAGS) $< -o $@
	@$(call print_progress)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\n\033[0;32mLIBFT HAS BEEN SUCCESSFULLY COMPILED! <3\033[0m"

all: $(NAME) 

B = .

.SILENT:

bonus: $(B)

$(B): $(OBJ) $(BONUS_OBJS)
	@$(C) $(FLAGS) $(SRC)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
fclean: clean
	@$(RM) $(NAME) $(BONUS_OBJS) $(OBJS)
re: fclean all
.PHONY: all fclean clean re 