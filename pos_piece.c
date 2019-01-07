/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:02:26 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:02:28 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_fill_tab_piece(t_info *t)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
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

int		ft_init_tab_piece(t_info *t)
{
	int i;
	int j;

	i = 0;
	t->nbr_pts = 0;
	while (i < t->height_piece)
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
	while (i < t->nbr_pts)
		t->tab_piece[i++] = (int *)malloc(sizeof(int) * 2);
	ft_fill_tab_piece(t);
	return (t->nbr_pts);
}

void	ft_heat_min(t_info *t, t_try_pos_piece *p, int x, int y)
{
	if (p->i != p->n)
	{
		p->p_is_free = ft_place_free(t, \
			y - t->tab_piece[p->n][0] + t->tab_piece[p->i][0], \
			x - t->tab_piece[p->n][1] + t->tab_piece[p->i][1]);
	}
	if (p->p_is_free)
	{
		t->heat_min_piece = ft_set_heat_min_piece(t, \
			y - t->tab_piece[p->n][0] + t->tab_piece[p->i][0], \
			x - t->tab_piece[p->n][1] + t->tab_piece[p->i][1]);
	}
	if (!p->p_is_free)
		t->heat_min_piece = 0;
}

int		ft_try_pos_piece(t_info *t, int y, int x)
{
	t_try_pos_piece p;

	p.p_is_free = 1;
	p.n = 0;
	p.i = 0;
	t->heat_min_global = 0;
	while (p.n < t->nbr_pts)
	{
		p.i = 0;
		t->heat_min_piece = 0;
		if (ft_piece_can_fit(t, p.n, y, x))
		{
			p.p_is_free = 1;
			while (p.i < t->nbr_pts && p.p_is_free)
			{
				ft_heat_min(t, &p, x, y);
				p.i++;
			}
			if (p.p_is_free)
				ft_set_ret(t, y - t->tab_piece[p.n][0], \
					x - t->tab_piece[p.n][1]);
		}
		p.n++;
	}
	return (t->heat_min_global);
}

int		ft_heat_of_point(t_info *t)
{
	int i;
	int j;

	t->chaleur = 1;
	while (t->chaleur <= t->chaleur_max)
	{
		i = 0;
		while (i < t->height_map)
		{
			j = 0;
			while (j < t->width_map)
			{
				if (t->map[i][j] == t->my_letter && \
					ft_check_if_chaleur_is_around(t, i, j, t->chaleur))
				{
					if (ft_try_pos_piece(t, i, j))
						return (0);
				}
				j++;
			}
			i++;
		}
		t->chaleur++;
	}
	return (1);
}
