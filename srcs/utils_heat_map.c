/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heat_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:02:36 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:02:38 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_init_heat_map2(t_info *t)
{
	int i;
	int j;

	i = 0;
	while (i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->map[i][j] == t->adv_letter)
				t->heat_map[i][j] = -1;
			else if (t->map[i][j] == t->my_letter)
				t->heat_map[i][j] = -2;
			else
				t->heat_map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	ft_init_heat_map(t_info *t, int *chaleur, int *next, int *zero)
{
	int i;

	i = 0;
	*chaleur = -1;
	*next = 2;
	*zero = 0;
	if (!(t->heat_map = (int **)malloc(sizeof(int *) * t->height_map)))
		return ;
	while (i < t->height_map)
	{
		if (!(t->heat_map[i] = (int *)malloc(sizeof(int) * t->width_map)))
			return ;
		i++;
	}
	ft_init_heat_map2(t);
}
