/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:02:02 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:02:05 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
void ft_put_heat_map(t_info *t)
{
	int i = 0;
	int j = 0;

	while (i <t->height_map)
	{
		j = 0;
		while( j < t->width_map)
		{
			ft_putnbr_fd(t->heat_map[i][j], 2);
			ft_putchar_fd(' ', 2);
			j++;
		}
		ft_putchar_fd('\n', 2);
		i++;
	}
}
*/

void	ft_put_next(t_info *t, int next, int i, int j)
{
	if (i - 1 >= 0)
	{
		if (t->heat_map[i - 1][j] == 0)
			t->heat_map[i - 1][j] = next;
	}
	if (i + 1 < t->height_map)
	{
		if (t->heat_map[i + 1][j] == 0)
			t->heat_map[i + 1][j] = next;
	}
	if (j - 1 >= 0)
	{
		if (t->heat_map[i][j - 1] == 0)
			t->heat_map[i][j - 1] = next;
	}
	if (j + 1 < t->width_map)
	{
		if (t->heat_map[i][j + 1] == 0)
			t->heat_map[i][j + 1] = next;
	}
}

int		ft_count_empty(t_info *t)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = 0;
	while (i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->heat_map[i][j] == 0)
				ret++;
			j++;
		}
		i++;
	}
	return (ret);
}

void	ft_zeros_to_max(t_info *t)
{
	int i;
	int j;

	i = 0;
	while (i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->heat_map[i][j] == 0)
				t->heat_map[i][j] = t->chaleur_max;
			if (t->heat_map[i][j] == -2)
				t->heat_map[i][j] = t->chaleur_max + 1;
			j++;
		}
		i++;
	}
}

void	ft_heat(t_info *t)
{
//	int i;
//	int j;
	int chaleur;
	int next;
	int zero;

	ft_init_heat_map(t, &chaleur, &next, &zero);
	while (zero != ft_count_empty(t))
	{
		zero = ft_count_empty(t);
		t->i = 0;
		while (t->i < t->height_map)
		{
			t->j = 0;
			while (t->j < t->width_map)
			{
				if (t->heat_map[t->i][t->j] == chaleur)
					ft_put_next(t, next, t->i, t->j);
				t->j++;
			}
			t->i++;
		}
		chaleur = next;
		next++;
	}
	t->chaleur_max = chaleur - 1;
	ft_zeros_to_max(t);
}
