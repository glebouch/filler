#ifndef FILLER_H
# define FILLER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "libft/includes/libft.h"

typedef struct	s_info
{
	int num_player;
	int width_map;
	int height_map;
	char letter;
	char **map;
	int **pos;
}				t_info;

typedef struct	s_piece
{
	int width_piece;
	int height_piece;
	char **piece;
}				t_piece;

#endif