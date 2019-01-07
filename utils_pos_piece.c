/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pos_piece.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:02:51 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:02:53 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_place_free(t_info *t, int y, int x)
{
	if (t->map[y][x] == '.')
		return (1);
	return (0);
}

int		ft_piece_can_fit(t_info *t, int n, int y, int x)
{
	if ((y - t->tab_piece[n][0] >= 0 && \
		y + t->height_piece - t->tab_piece[n][0] <= t->height_map) && \
		(x - t->tab_piece[n][1] >= 0 && \
		x + t->width_piece - t->tab_piece[n][1] <= t->width_map))
		return (1);
	return (0);
}

int		ft_set_heat_min_piece(t_info *t, int y, int x)
{
	if (t->heat_map[y][x] > 0 && (!t->heat_min_piece || \
		t->heat_min_piece > t->heat_map[y][x]))
		return (t->heat_map[y][x]);
	return (t->heat_min_piece);
}

void	ft_set_ret(t_info *t, int y, int x)
{
	if (!t->heat_min_global || t->heat_min_global > t->heat_min_piece)
	{
		if (t->heat_min_piece > 0)
			t->heat_min_global = t->heat_min_piece;
		t->i_ret = y;
		t->j_ret = x;
	}
}

int		ft_check_if_chaleur_is_around(t_info *t, int i, int j, int chaleur)
{
	if ((i - 1 >= 0 && t->heat_map[i - 1][j] == chaleur) || \
		(i + 1 < t->height_map && t->heat_map[i + 1][j] == chaleur) || \
		(j - 1 >= 0 && t->heat_map[i][j - 1] == chaleur) || \
		(j + 1 < t->width_map && t->heat_map[i][j + 1] == chaleur))
		return (1);
	return (0);
}
