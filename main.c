/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:02:12 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 17:02:20 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_tpiece_to_null(t_info *t)
{
	int i;

	i = 0;
	while (i < t->height_piece)
		t->piece[i++] = NULL;
}

int		ft_parse_piece(t_info *t)
{
	char	*line;
	char	**tmp;

	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	t->height_piece = (tmp[1]) ? ft_atoi(tmp[1]) : 0;
	t->width_piece = (tmp[2]) ? ft_atoi(tmp[2]) : 0;
	ft_free_tab_char(tmp);
	free(line);
	if (!t->height_piece || !t->width_piece)
	{
		ft_free_tab_char(t->map);
		return (0);
	}
	if (!(t->piece = (char **)malloc(sizeof(char *) * (t->height_piece + 1))))
		return (0);
	ft_tpiece_to_null(t);
	if (!ft_parse_piece2(t))
	{
		while (get_next_line(0, &line) > 0)
			free(line);
		return (0);
	}
	return (1);
}

int		ft_parse_map(t_info *t)
{
	char	*line;
	char	**tmp;
	int		i;

	i = 0;
	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	t->height_map = (tmp[1]) ? ft_atoi(tmp[1]) : 0;
	t->width_map = (tmp[2]) ? ft_atoi(tmp[2]) : 0;
	ft_free_tab_char(tmp);
	free(line);
	if (!(t->map = (char **)malloc(sizeof(char *) * (t->height_map + 1))))
		return (0);
	while (i < t->height_map)
		t->map[i++] = NULL;
	get_next_line(0, &line);
	free(line);
	if (!ft_parse_map2(t))
	{
		while (get_next_line(0, &line) > 0)
			free(line);
		return (0);
	}
	return (1);
}

int		ft_infos(t_info *t)
{
	char	*line;
	char	*name;

	get_next_line(0, &line);
	if (!line)
		return (0);
	name = (line) ? ft_strstr(line, "glebouch.filler") : NULL;
	t->num_player = (line[10]) ? ft_atoi(&line[10]) : 0;
	t->my_letter = (t->num_player == 1) ? 'O' : 'X';
	t->adv_letter = (t->my_letter == 'X') ? 'O' : 'X';
	free(line);
	if (!t->num_player || !name)
	{
		while (get_next_line(0, &line) > 0)
			free(line);
		return (0);
	}
	return (1);
}

int		main(void)
{
	t_info t;

	ft_bzero((void *)&t, sizeof(t));
	if (!ft_infos(&t))
		return (0);
	while (1)
	{
		t.i_ret = 0;
		t.j_ret = 0;
		if (!ft_parse_map(&t) || !ft_parse_piece(&t))
			return (0);
		if (!ft_init_tab_piece(&t))
			return (0);
		ft_heat(&t);
		t.end = ft_heat_of_point(&t);
		ft_putnbr_fd(t.i_ret, 1);
		ft_putchar(' ');
		ft_putnbr_fd(t.j_ret, 1);
		ft_putchar('\n');
		ft_free_all(&t);
		if (t.end)
			return (0);
	}
	return (0);
}
