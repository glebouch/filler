#include "filler.h"

void ft_fill_tab_piece(t_piece *p)
{
	int i = 0;
	int j;
	int k = 0;

	while (i < p->height_piece)
	{
		j = 0;
		while (j < p->width_piece)
		{
			if (p->piece[i][j] == '*')
			{
				p->tab_piece[k][0] = i;
				p->tab_piece[k][1] = j;
			}
			j++;
		}
		i++;
	}
}

void ft_init_tab_piece(t_piece *p)
{
	int i = 0;
	int j;
	int nbr_pts = 0;

	while(i < p->height_piece)
	{
		j = 0;
		while (j < p->width_piece)
		{
			if (p->piece[i][j] == '*')
				nbr_pts++;
			j++;
		}
		i++;
	}
	i = 0;
	p->tab_piece = (int **)malloc(sizeof(int *) * nbr_pts);
	while(i < nbr_pts)
		p->tab_piece[i++] = (int *)malloc(sizeof(int) * 2);
	ft_fill_tab_piece(p);
	return(nbr_pts);
}

int ft_try_pos_piece(t_info *t, t_piece *p, int i, int j)
{
	int k = 0;
	int i = 0;
	int nbr_pts;

	nbr_pts = ft_init_tab_piece(p);
	while(i < nbr_pts)
	{
		if(t->map[][] == '.')
			

	}
}

int ft_heat_of_point(t_info *t, t_piece *p, int i, int j)
{
	int i = 0;
	int j;
	int chaleur = 1;

	while(chaleur <= t->chaleur_max)
	{
		while (i < t->height_map)
		{
			j = 0;
			while (j < t->width_map)
			{
				if (t->map[i][j] == t->myletter && t->heat_map[i][j] == chaleur)
				{
					if(ft_try_pos_piece(t, p, i, j))
						return(0);
				}
				j++;
			}
			i++;
		}
		chaleur++;
	}
	return(0);
}


void ft_a_voir(t_info *t, t_piece *p)
{
	int i = 0;
	int j;

	while (i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->map[i][j] == t->myletter)
				ft_heat_of_point(t, p, i, j);
			j++;
		}
		i++;
	}
}