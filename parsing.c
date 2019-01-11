/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 10:19:17 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/11 10:19:19 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_verif_line_piece(t_info *t, char *line)
{
	int j;

	j = 0;
	while (line[j] && (line[j] == '.' || line[j] == '*'))
		j++;
	if (j == t->width_piece)
		return (1);
	ft_free_tab_char(t->map);
	ft_free_tab_char(t->piece);
	return (0);
}

int		ft_parse_piece2(t_info *t)
{
	int		i;
	char	*line;

	i = 0;
	while (i < t->height_piece)
	{
		get_next_line(0, &line);
		if (!ft_verif_line_piece(t, line))
		{
			free(line);
			return (0);
		}
		t->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
	t->piece[i] = NULL;
	return (1);
}

int		ft_verif_line_map(t_info *t, char *tmp1, char *tmp2, int i)
{
	int j;

	j = 0;
	if (ft_atoi(tmp1) == i)
	{
		while (tmp2[j] && (tmp2[j] == '.' || tmp2[j] == 'O' || tmp2[j] == 'X'))
			j++;
		if (j == t->width_map)
			return (1);
	}
	ft_free_tab_char(t->map);
	return (0);
}

int		ft_parse_map2(t_info *t)
{
	int		i;
	char	*line;
	char	**tmp;

	i = 0;
	while (i < t->height_map)
	{
		get_next_line(0, &line);
		tmp = ft_strsplit(line, ' ');
		if (!ft_verif_line_map(t, tmp[0], tmp[1], i))
		{
			ft_free_tab_char(tmp);
			free(line);
			return (0);
		}
		t->map[i] = ft_strdup(tmp[1]);
		free(line);
		ft_free_tab_char(tmp);
		i++;
	}
	t->map[i] = NULL;
	return (1);
}
