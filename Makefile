NAME = glebouch.filler

INCLUDES = includes

SRC = main.c heat_map.c pos_piece.c frees.c utils_pos_piece.c utils_heat_map.c parsing.c

LIB = ./libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g3

OBJ = $(SRC:.c=.o)

CC = gcc

all : mlib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB) -I $(INCLUDES)

%.o : %.c $(INCLUDES)/filler.h
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDES)

mlib :
	make -C ./libft/

clean :
	@make clean -C ./libft/
	@rm $(OBJ)
	
fclean : clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re : 
	@make fclean
	@make all
