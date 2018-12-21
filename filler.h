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
	int heat_min_global;
	int heat_min_piece;
	char **map;
	int **pos;
	int **heat_map;
	int i_ret;
	int j_ret;
	int nbr_pts;
	int width_piece;
	int height_piece;
	char **piece;
	int **tab_piece;
}				t_info;


void	ft_init_heat_map(t_info *t);
int ft_heat_of_point(t_info *t);
void ft_free_all(t_info *t);
void ft_put_heat_map(t_info *t);

#endif