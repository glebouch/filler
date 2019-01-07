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

/*
void ft_print_infos(t_info *t)
{
	int i = 0;
	int j = 0;

	while (i < t->height_map)
		ft_putendl_fd(t->map[i++], 2);
	while (j < t->height_piece)
		ft_putendl_fd(t->piece[j++], 2);
	ft_put_tab_piece(t);
	ft_put_heat_map(t);
//	sleep(1);
}

int		ft_size(uintmax_t n)
{
	int	size;

	size = 1;
	while (n / 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}
*/

void	ft_parse_piece(t_info *t)
{
	char	*line;
	int		i;
	char	**tmp;

	i = 0;
	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	t->height_piece = ft_atoi(tmp[1]);
	t->width_piece = ft_atoi(tmp[2]);
	ft_free_tab_char(tmp);
	free(line);
	if (!(t->piece = (char **)malloc(sizeof(char *) * (t->height_piece + 1))))
		return ;
	while (i < t->height_piece)
	{
		get_next_line(0, &line);
		t->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
	t->piece[i] = NULL;
	ft_init_tab_piece(t);
}

void	ft_parse_map(t_info *t)
{
	char	*line;
	int		i;
	char	**tmp;

	i = 0;
	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	t->height_map = ft_atoi(tmp[1]);
	t->width_map = ft_atoi(tmp[2]);
	ft_free_tab_char(tmp);
	free(line);
	if (!(t->map = (char **)malloc(sizeof(char *) * (t->height_map + 1))))
		return ;
	get_next_line(0, &line);
	free(line);
	while (i < t->height_map)
	{
		get_next_line(0, &line);
		tmp = ft_strsplit(line, ' ');
		t->map[i] = ft_strdup(tmp[1]);
		free(line);
		ft_free_tab_char(tmp);
		i++;
	}
	t->map[i] = NULL;
}

void	ft_infos(t_info *t)
{
	char	*line;

	get_next_line(0, &line);
	t->num_player = ft_atoi(line + 10);
	t->my_letter = (t->num_player == 1) ? 'O' : 'X';
	t->adv_letter = (t->my_letter == 'X') ? 'O' : 'X';
	free(line);
}

int		main(void)
{
	t_info t;

	ft_bzero((void *)&t, sizeof(t));
	ft_infos(&t);
	while (1)
	{
		t.i_ret = 0;
		t.j_ret = 0;
		ft_parse_map(&t);
		ft_heat(&t);
		ft_parse_piece(&t);
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
