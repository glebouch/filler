NAME = glebouch.filler

SRC = main.c heat_map.c pos_piece.c frees.c utils_pos_piece.c utils_heat_map.c

LIB = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror

CC = clang

all : $(NAME)

$(NAME) : mlib
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIB)

mlib :
	@make -C ./libft/

clean :
	@make clean -C ./libft/
	
fclean :
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re : fclean	all
