#ifndef FILLER_H
# define FILLER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include "libft/includes/libft.h"

typedef struct	s_info
{
	int fd;
	int num_player;
	int width_map;
	int height_map;
	char my_letter;
	char adv_letter;
	int chaleur_max;
	char **map;
	int **pos;
	int **heat_map;
}				t_info;

typedef struct	s_piece
{
	int width_piece;
	int height_piece;
	char **piece;
	int **tab_piece;
}				t_piece;

void	ft_init_heat_map(t_info *t);

#endif