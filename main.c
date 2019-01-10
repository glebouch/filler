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

int		ft_verif_line_piece(t_info *t, char *line)
{
	ft_putstr_fd("line piece\n", 2);
	ft_putstr_fd(t->map[0], 2);
	int j;

	j = 0;
	while(line[j] && (line[j] == '.' || line[j] == '*'))
		j++;
	if (j == t->width_piece)
		return (1);
	ft_free_tab_char(t->map);
	ft_free_tab_char(t->piece);
	return(0);
}

int		ft_parse_piece2(t_info *t)
{
	int i;
	char *line;

	i = 0;
	while (i < t->height_piece)
	{
		get_next_line(0, &line);
		if(!ft_verif_line_piece(t, line))
		{
			free(line);
			return(0);
		}
		t->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
	t->piece[i] = NULL;
	return (1);
}

int		ft_parse_piece(t_info *t)
{
	char	*line;
	char	**tmp;
	int i = 0;

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
	while (i < t->height_piece)
		t->piece[i++] = NULL;
	if (!ft_parse_piece2(t))
	{
//		ft_free_tab_char(t->map);
//		ft_free_tab_char(t->piece);
		ft_putstr_fd("error parse piece\n", 2);
		return (0);
	}
	ft_init_tab_piece(t);
	return (1);
}

int		ft_verif_line_map(t_info *t, char *tmp1, char *tmp2, int i)
{
	ft_putstr_fd("line map\n", 2);
	int j;

	j = 0;
	if (ft_atoi(tmp1) == i)
	{
		while (tmp2[j] && (tmp2[j] == '.' || tmp2[j] == 'O' || tmp2[j] == 'X'))
			j++;
		if (j == t->width_map)
			return (1);
	}
	ft_putstr_fd("line maperror\n", 2);
	ft_free_tab_char(t->map);
	return (0);
}

int		ft_parse_map2(t_info *t)
{
	int i;
	char *line;
	char **tmp;

	i = 0;
	while (i < t->height_map)
	{
		get_next_line(0, &line);
		tmp = ft_strsplit(line, ' ');
		if (!ft_verif_line_map(t, tmp[0], tmp[1], i))
		{
			ft_free_tab_char(tmp);
			free(line);
//			ft_putstr_fd("on free\n", 2);
			return(0);
		}
//		ft_putstr_fd(tmp[1], 2);
//		free(t->map[i]);
		t->map[i] = ft_strdup(tmp[1]);
		free(line);
		ft_free_tab_char(tmp);
		i++;
	}
	t->map[i] = NULL;
	return(1);
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
	{
		ft_putstr_fd("error malloc\n", 2);
		return (0);
	}
	while(i < t->height_map)
		t->map[i++] = NULL;
	get_next_line(0, &line);
	free(line);
	if (!ft_parse_map2(t))
	{
		ft_putstr_fd("error parse map\n", 2);
		return(0);
	}
	return(1);
}

int		ft_infos(t_info *t)
{
	char	*line;
	char	*name;

	get_next_line(0, &line);
//	ft_putstr_fd(line, 2);
	name = ft_strstr(line, "glebouch.filler");
	t->num_player = (line[10]) ? ft_atoi(&line[10]) : 0;
	t->my_letter = (t->num_player == 1) ? 'O' : 'X';
	t->adv_letter = (t->my_letter == 'X') ? 'O' : 'X';
//	ft_putstr_fd(line, 2);
	free(line);
	if (!t->num_player || !name)
	{
//		ft_putstr_fd("tamere", 2);
		return (0);
	}
	return (1);
}

int		main(void)
{
	t_info t;

	ft_bzero((void *)&t, sizeof(t));
	if (!ft_infos(&t))
		return(0);
	while (1)
	{
		t.i_ret = 0;
		t.j_ret = 0;
		if(!ft_parse_map(&t) || !ft_parse_piece(&t))
		{
			ft_putstr_fd("tagrandmere", 2);
			return (0);
		}
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
