NAME = glebouch.filler

INCLUDES = includes

SRC = 	srcs/main.c \
		srcs/heat_map.c \
		srcs/pos_piece.c \
		srcs/frees.c \
		srcs/utils_pos_piece.c \
		srcs/utils_heat_map.c \
		srcs/parsing.c

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
	@rm -f $(OBJ)
	
fclean : clean
	@make fclean -C ./libft/
	@/bin/rm -f $(NAME)

re : 
	@make fclean
	@make all
