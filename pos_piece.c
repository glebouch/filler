#include "filler.h"
void ft_put_tab_piece(t_info *t)
{
	int i = 0;
	int j = 0;

	while (i < t->nbr_pts)
	{
		j = 0;
		while( j < 2)
		{
			ft_putnbr_fd(t->tab_piece[i][j], 2);
			ft_putchar_fd(' ', 2);
			j++;
		}
		ft_putchar_fd('\n', 2);
		i++;
	}
}
void ft_fill_tab_piece(t_info *t)
{
	int i = 0;
	int j;
	int k = 0;

	while (i < t->height_piece)
	{
		j = 0;
		while (j < t->width_piece)
		{
			if (t->piece[i][j] == '*')
			{
				t->tab_piece[k][0] = i;
				t->tab_piece[k][1] = j;
				k++;
			}
			j++;
		}
		i++;
	}
}

int ft_init_tab_piece(t_info *t)
{
	ft_putstr_fd("ft_init_tab_piece\n", 2);
	int i = 0;
	int j;
	

	t->nbr_pts = 0;
	while(i < t->height_piece)
	{
		j = 0;
		while (j < t->width_piece)
		{
			if (t->piece[i][j] == '*')
				t->nbr_pts++;
			j++;
		}
		i++;
	}
	i = 0;
	t->tab_piece = (int **)malloc(sizeof(int *) * t->nbr_pts);
	while(i < t->nbr_pts)
		t->tab_piece[i++] = (int *)malloc(sizeof(int) * 2);
	ft_fill_tab_piece(t);
//	ft_put_tab_piece(t);

	ft_putstr_fd("ft_init_tab_piece fin\n", 2);
	return(t->nbr_pts);
}

int ft_place_free(t_info *t, int y, int x)
{
	ft_putstr_fd("ft_place_free\n", 2);
	ft_putnbr_fd(y, 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(x, 2);
	ft_putchar_fd(' ',2);
	ft_putchar_fd(t->map[y][x], 2);
	if (t->map[y][x] == '.')
		return (1);
	ft_putstr_fd("ft_place_not free at \n", 2);
	ft_putnbr_fd(y, 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(x, 2);
	return (0);
}

int ft_piece_can_fit(t_info *t, int n, int y, int x)
{
	ft_putstr_fd("ft_piece_can_fit\n", 2);
	ft_putnbr_fd(y - t->tab_piece[n][0], 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(t->height_map, 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(y + t->height_piece - t->tab_piece[n][0], 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(x - t->tab_piece[n][1], 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(t->width_map, 2);
	ft_putchar_fd(' ',2);
	ft_putnbr_fd(x + t->width_piece - t->tab_piece[n][1], 2);
	ft_putchar_fd(' ',2);
	if((y - t->tab_piece[n][0] >= 0 && y + t->height_piece - t->tab_piece[n][0] <= t->height_map) && \
		(x - t->tab_piece[n][1] >= 0 && x + t->width_piece - t->tab_piece[n][1] <= t->width_map))
		return (1);
	ft_putstr_fd("ft_piece_cantttttt_fit\n", 2);
	return (0);
}

int ft_set_heat_min_piece(t_info *t, int y, int x)
{
	ft_putstr_fd("ft_set_heat_min_piece\n", 2);
	if (t->heat_map[y][x] > 0 && (!t->heat_min_piece || t->heat_min_piece > t->heat_map[y][x]))
		return (t->heat_map[y][x]);
	return (t->heat_min_piece);
}

void ft_set_ret(t_info *t, int y, int x)
{
	ft_putstr_fd("ft_set_ret\n", 2);
	if (!t->heat_min_global || t->heat_min_global > t->heat_min_piece)
	{
		if(t->heat_min_piece > 0)
		t->heat_min_global = t->heat_min_piece;
		t->i_ret = y;
		t->j_ret = x;
		ft_putchar_fd(' ', 2);
		ft_putnbr_fd(t->i_ret, 2);
		ft_putchar_fd(' ', 2);
		ft_putnbr_fd(t->j_ret, 2);
	}
}

int ft_try_pos_piece(t_info *t, int y, int x)
{
	ft_putstr_fd("ft_try_pos_piece\n", 2);
	int p_is_free = 1;
	int n = 0;
	int i = 0;

	ft_init_tab_piece(t);
	while (n < t->nbr_pts && ft_piece_can_fit(t, n, y, x))
	{
		ft_putstr_fd("n = ", 2);
		ft_putnbr_fd(n, 2);
		i = 0;
		t->heat_min_piece = 0;
		while (i < t->nbr_pts && p_is_free)
		{
			ft_putstr_fd("i = ", 2);
			ft_putnbr_fd(i, 2);
			p_is_free = 1;
			if (i != n)
			{
				ft_putchar_fd(' ',2);
				ft_putnbr_fd(x,2);
				ft_putchar_fd(' ',2);
				ft_putnbr_fd(t->tab_piece[n][1],2);
				ft_putchar_fd('i',2);
				ft_putnbr_fd(i,2);
				ft_putchar_fd('t',2);
				ft_putnbr_fd(t->tab_piece[i][1],2);
				ft_putchar_fd('a',2);
				ft_putnbr_fd(x + t->tab_piece[n][1] - t->tab_piece[i][1],2);
				ft_putchar_fd(' ',2);
				p_is_free = ft_place_free(t, y + t->tab_piece[n][0] - t->tab_piece[i][0], \
						x + t->tab_piece[n][1] - t->tab_piece[i][1]);
				ft_putstr_fd("\ndans if p_is_free = \n", 2);
				ft_putnbr_fd(p_is_free, 2);
			}
			ft_putstr_fd("\nici p_is_free = \n", 2);
			ft_putnbr_fd(p_is_free, 2);
			if (p_is_free)
			{
				t->heat_min_piece = ft_set_heat_min_piece(t, y - t->tab_piece[n][0] + t->tab_piece[i][0],
					x - t->tab_piece[n][1] + t->tab_piece[i][1]);
				ft_putnbr_fd(y, 2);
				ft_putchar_fd(' ', 2);
				ft_putnbr_fd(x, 2);
				ft_putchar_fd(' ', 2);
				ft_putnbr_fd(y - t->tab_piece[n][0] + t->tab_piece[i][0], 2);
				ft_putchar_fd(' ', 2);
				ft_putnbr_fd(x - t->tab_piece[n][1] + t->tab_piece[i][1], 2);
				ft_putchar_fd(' ', 2);
				ft_putnbr_fd(t->heat_map[y - t->tab_piece[n][0] + t->tab_piece[i][0]][x - t->tab_piece[n][1] + t->tab_piece[i][1]], 2);
				ft_putchar_fd(' ', 2);
				ft_putnbr_fd(t->heat_min_piece, 2);
			}
			ft_putstr_fd("la\n", 2);
			if (!p_is_free)
				t->heat_min_global = 0;
			i++;
		}
		if (p_is_free)
		{
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(t->tab_piece[n][0], 2);
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(t->tab_piece[n][1], 2);
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(y, 2);
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(x, 2);
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(t->heat_min_global, 2);
			ft_putchar_fd(' ', 2);
			ft_putnbr_fd(t->heat_min_piece, 2);
			ft_putchar_fd('\n', 2);
			ft_put_heat_map(t);

			ft_set_ret(t, y - t->tab_piece[n][0], x - t->tab_piece[n][1]);
		}
		n++;
	}
	ft_putstr_fd("ft_try_pos_piece fin\n", 2);
	ft_putnbr_fd(t->heat_min_global, 2);
	return(t->heat_min_global);
}

int ft_check_if_chaleur_is_around(t_info *t, int i, int j, int chaleur)
{
	if((i - 1 >= 0 && t->heat_map[i - 1][j] == chaleur) || \
		(i + 1 < t->height_map && t->heat_map[i + 1][j] == chaleur) || \
		(j - 1 >= 0 && t->heat_map[i][j - 1] == chaleur) || \
		(j + 1 < t->width_map && t->heat_map[i][j + 1] == chaleur))
		return(1);
	return(0);
}

int ft_heat_of_point(t_info *t)
{
	int i = 0;
	int j;
	int chaleur = 1;

	while(chaleur <= t->chaleur_max)
	{
//		ft_putnbr_fd(chaleur, 2);
//		ft_putstr_fd("w1\n", 2);
		i = 0;
		while (i < t->height_map)
		{
//			ft_putstr_fd("w2\n", 2);
			j = 0;
			while (j < t->width_map)
			{
//				ft_putstr_fd("w3\n", 2);
//				ft_putchar_fd(t->map[i][j], 2);
//				ft_putchar_fd(':', 2);
//				ft_putnbr_fd(t->heat_map[i][j], 2);
//				ft_putchar_fd(' ', 2);
//				ft_putchar_fd(t->map[i][j], 2);
//				ft_putchar_fd(t->my_letter, 2);
//				ft_putnbr_fd(ft_check_if_chaleur_is_around(t, i, j, chaleur), 2);
				if (t->map[i][j] == t->my_letter && ft_check_if_chaleur_is_around(t, i, j, chaleur))
				{
//					ft_putnbr_fd(t->map[i][j], 2);
					ft_putstr_fd("nique", 2);
					if(ft_try_pos_piece(t, i, j))
						return(0);
				}
				j++;
			}
//			ft_putchar_fd('\n', 2);
			i++;
		}
		chaleur++;
	}
	ft_putstr_fd("heat point fin\n", 2);
	ft_free_all(t);
	return(0);

}
