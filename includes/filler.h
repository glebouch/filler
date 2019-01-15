/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glebouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:24:54 by glebouch          #+#    #+#             */
/*   Updated: 2019/01/07 18:25:03 by glebouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/includes/libft.h"

typedef struct	s_info
{
	int		fd;
	int		num_player;
	int		width_map;
	int		height_map;
	char	my_letter;
	char	adv_letter;
	int		chaleur_max;
	int		chaleur;
	int		heat_min_global;
	int		heat_min_piece;
	char	**map;
	int		**pos;
	int		**heat_map;
	int		i_ret;
	int		j_ret;
	int		nbr_pts;
	int		width_piece;
	int		height_piece;
	char	**piece;
	int		**tab_piece;
	int		end;
	int		i;
	int		j;
}				t_info;

typedef struct	s_try_pos_piece
{
	int i;
	int n;
	int p_is_free;
}				t_try_pos_piece;

int				ft_place_free(t_info *t, int y, int x);
int				ft_piece_can_fit(t_info *t, int n, int y, int x);
int				ft_set_heat_min_piece(t_info *t, int y, int x);
void			ft_set_ret(t_info *t, int y, int x);
int				ft_check_if_chaleur_is_around(t_info *t, int i, int j, int ch);
void			ft_heat(t_info *t);
void			ft_init_heat_map(t_info *t, int *chaleur, int *next, int *zero);
int				ft_heat_of_point(t_info *t);
void			ft_free_all(t_info *t);
void			ft_put_heat_map(t_info *t);
int				ft_init_tab_piece(t_info *t);
void			ft_put_tab_piece(t_info *t);
void			ft_free_tab_char(char **tab);
int				ft_parse_piece2(t_info *t);
int				ft_parse_map2(t_info *t);

#endif
