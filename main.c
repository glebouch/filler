
#include "filler.h"

void ft_print_infos(t_info *t)
{
	int i = 0;
	int j = 0;

	while (i < t->height_map)
		ft_putendl_fd(t->map[i++], 2);
	while (j < t->height_piece)
		ft_putendl_fd(t->piece[j++], 2);
	ft_put_heat_map(t);
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

void ft_free_tab_char(char **tab)
{
	int i = 0;
//	ft_putstr_fd("free d\n", 2);
	if (!tab)
		return ;
	while(tab[i])
	{
		// ft_putstr_fd(tab[i], 2);
		free(tab[i]);
		// ft_putstr_fd("free b\n", 2);
		// ft_putnbr_fd(i, 2);
		// ft_putstr_fd("\n", 2);
		i++;
	}
//	ft_putstr_fd("free f-1\n", 2);
	free(tab);
//	ft_putstr_fd("free f\n", 2);
}

void ft_free_tab_int(int **tab, int height)
{
	int i = 0;

	while (i < height)
		free(tab[i++]);
	free(tab);

}

void ft_free_all(t_info *t)
{
//	ft_putstr_fd("free 1\n", 2);
//	ft_print_infos(t);
	ft_free_tab_char(t->map);
//	ft_putstr_fd("free2\n", 2);
	 ft_free_tab_char(t->piece);
//	ft_putstr_fd("free3\n", 2);
	ft_free_tab_int(t->tab_piece, t->nbr_pts);
//	ft_putstr_fd("free4\n", 2);
	ft_free_tab_int(t->heat_map, t->height_map);
//	ft_putstr_fd("free5\n", 2);
}

void ft_parse_piece(t_info *t)
{
	ft_putstr_fd("parse piece\n", 2);
	char *line;
	int i = 0;
	char **tmp;

	get_next_line(0, &line);
//	ft_putstr_fd(line, 2);
	tmp = ft_strsplit(line, ' ');
	t->height_piece = ft_atoi(tmp[1]);
	t->width_piece = ft_atoi(tmp[2]);
	ft_free_tab_char(tmp);
	free(line);
	if (!(t->piece = (char **)malloc(sizeof(char *) * (t->height_piece + 1))))
		return ;
	while(i < t->height_piece)
	{
		get_next_line(0, &line);
		t->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
	t->piece[i] = NULL;
	ft_init_tab_piece(t);
	ft_putstr_fd("parse piece fin\n", 2);
	ft_print_infos(t);
}

void ft_parse_map(t_info *t)
{
	ft_putstr_fd("parse map\n", 2);
	char *line;
	int i = 0;
	char **tmp;

	get_next_line(0, &line);
//	ft_putstr_fd(line, 2);
	tmp = ft_strsplit(line, ' ');
	t->height_map = ft_atoi(tmp[1]);
	t->width_map = ft_atoi(tmp[2]);
	ft_free_tab_char(tmp);
	free(line);
	if (!(t->map = (char **)malloc(sizeof(char *) * (t->height_map + 1))))
		return ;
	i = 0;
	get_next_line(0, &line);
//	ft_putstr_fd(line, 2);
	while(i < t->height_map)
	{
		get_next_line(0, &line);
//		ft_putstr_fd(line, 2);
		tmp = ft_strsplit(line, ' ');
		t->map[i] = ft_strdup(tmp[1]);
		free(line);
		ft_free_tab_char(tmp);
		i++;
	}
	t->map[i] = NULL;
	ft_putstr_fd("parse map fin\n", 2);
}


void ft_infos(t_info *t)
{
	ft_putstr_fd("info\n", 2);
	char *line;
//	char **tmp;

	get_next_line(0, &line);
	t->num_player = ft_atoi(line + 10);
	t->my_letter = (t->num_player == 1) ? 'O' : 'X';	
	t->adv_letter = (t->my_letter == 'X') ? 'O' : 'X';
	free(line);
	ft_putnbr_fd(t->num_player, 2);
	ft_putnbr_fd(t->height_map, 2);
	ft_putnbr_fd(t->width_map, 2);
	ft_putstr_fd("info fin\n", 2);
}

int main(int ac, char **av)
{
	t_info t;

//	ft_putnbr_fd(3, 1);
	ft_bzero((void *)&t, sizeof(t));
	ft_infos(&t);
	while(1)
	{
	ft_parse_map(&t);
	ft_init_heat_map(&t);
	ft_parse_piece(&t);
	ft_heat_of_point(&t);
//	while(get_next_line(0, &line))
//	{
//		ft_putendl_fd(line, 2);
//	}
//	ft_putstr_fd(line, 2);

	ft_putnbr_fd(t.i_ret, 1);
	ft_putchar(' ');
	ft_putnbr_fd(t.j_ret, 1);
	ft_putchar('\n');
	}
	return (0);
}