
#include "filler.h"

void ft_print_infos(t_info *t, t_piece *p)
{
	int i = 0;
	int j = 0;

	while (i < t->height_map)
		ft_putendl_fd(t->map[i++], 2);
	while (j < p->height_piece)
		ft_putendl_fd(p->piece[j++], 2);
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

void ft_free_tab(char **tab)
{
	int i = 0;

	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void ft_parse_piece(t_info *t, t_piece *p)
{
	char *line;
	int i = 0;
	char **tmp;

	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	p->height_piece = ft_atoi(tmp[1]);
	p->width_piece = ft_atoi(tmp[2]);
	ft_free_tab(tmp);
	free(line);
	if (!(p->piece = (char **)malloc(sizeof(char *) * p->height_piece)))
		return ;
	while(i < p->height_piece)
	{
		get_next_line(0, &line);
		p->piece[i] = ft_strdup(line);
		free(line);
		i++;
	}
	ft_print_infos(t, p);
}

void ft_parse_map(t_info *t)
{
	char *line;
	int i = 0;
	char **tmp;

	if (!(t->map = (char **)malloc(sizeof(char *) * t->height_map)))
		return ;
	i = 0;
	get_next_line(0, &line);
	while(i < t->height_map)
	{
		get_next_line(0, &line);
		tmp = ft_strsplit(line, ' ');
		t->map[i] = ft_strdup(tmp[1]);
		free(line);
		ft_free_tab(tmp);
		i++;
	}
}


void ft_infos(t_info *t)
{
	char *line;
	char **tmp;

	get_next_line(0, &line);
	t->num_player = ft_atoi(line + 10);
	t->letter = (t->num_player == 1) ? 'O' : 'X';
	free(line);
	get_next_line(0, &line);
	tmp = ft_strsplit(line, ' ');
	t->height_map = ft_atoi(tmp[1]);
	t->width_map = ft_atoi(tmp[2]);
	ft_free_tab(tmp);
	free(line);
//	ft_putnbr_fd(t->num_player, 2);
//	ft_putnbr_fd(t->height_map, 2);
//	ft_putnbr_fd(t->width_map, 2);
}

int main()
{
	t_info t;
	t_piece p;

	ft_infos(&t);
	ft_parse_map(&t);
	ft_parse_piece(&t, &p);
//	while(get_next_line(0, &line))
//	{
//		ft_putendl_fd(line, 2);
//	}
//	ft_putstr_fd(line, 2);
	ft_putnbr(12);
	ft_putchar(' ');
	ft_putnbr(14);
	ft_putchar('\n');
	return (0);
}