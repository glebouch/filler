/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:01:40 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:01:46 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_free_tab_char(char **tab)
{
	int i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_tab_int(int **tab, int height)
{
	int i;

	i = 0;
	while (i < height)
		free(tab[i++]);
	free(tab);
}

int		ft_free_all(t_info *t)
{
	ft_free_tab_char(t->map);
	ft_free_tab_char(t->piece);
	ft_free_tab_int(t->tab_piece, t->nbr_pts);
	ft_free_tab_int(t->heat_map, t->height_map);
	if (t->end)
		get_next_line(0, NULL);
	return (!t->end);
}
