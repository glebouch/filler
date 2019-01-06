 #include "filler.h"

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

void ft_put_next(t_info *t, int next, int i, int j)
{
//	ft_putstr_fd("put next\n", 2);
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
//	ft_putstr_fd("put next fin\n", 2);
}

int ft_count_empty(t_info *t)
{
//	ft_putstr_fd("count empty\n", 2);
	int i = 0;
	int j = 0;
	int ret = 0;

	while(i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->heat_map[i][j] == 0)
				ret++;
//			ft_putnbr_fd(t->heat_map[i][j], 2);
//			ft_putchar_fd(' ', 2);
			j++;
		}
//		ft_putchar_fd('\n', 2);
		i++;
	}
//	sleep(1);
//	ft_putstr_fd("count empty fin\n", 2);
//	ft_putnbr_fd(ret, 2);
	return (ret);
}

void ft_zeros_to_max(t_info *t)
{
	int i = 0;
	int j;
//ft_putnbr(t->chaleur_max);
	while(i < t->height_map)
	{
		j = 0;
		while (j < t->width_map)
		{
			if (t->heat_map[i][j] == 0)
				t->heat_map[i][j] = t->chaleur_max;
			if (t->heat_map[i][j] == -2)
				t->heat_map[i][j] = t->chaleur_max + 1;
//			ft_putnbr_fd(i, 2);
//			ft_putnbr_fd(j, 2);
//			ft_putnbr_fd(t->heat_map[i][j], 2);
			j++;
			
//			ft_putchar_fd(' ', 2);
		}
//		ft_putchar_fd('\n', 2);
		i++;
	}
//	ft_putnbr(t->chaleur_max);
//	sleep(3);
}

void ft_heat(t_info *t)
{
//	ft_putstr_fd("heat\n", 2);
	int i = 0;
	int j = 0;
	int chaleur = -1;
	int next = 2;
	int zero = 0;

	while(zero != ft_count_empty(t))
	{
		zero = ft_count_empty(t);
//		ft_putnbr_fd(zero, 2);
		i = 0;
		while(i < t->height_map)
		{
//			ft_putstr_fd("la", 2);
			j = 0;
			while (j < t->width_map)
			{
//				ft_putnbr_fd(chaleur, 2);
//				ft_putnbr_fd(next, 2);
				if (t->heat_map[i][j] == chaleur)
					ft_put_next(t, next, i, j);
				j++;
			}
			i++;
		}
		chaleur = next;
		next++;
//		ft_putnbr_fd(chaleur, 2);
//		ft_putnbr_fd(next, 2);
	}
	t->chaleur_max = chaleur - 1;
//	ft_putstr_fd("t->chaleur_max=", 2);
//	ft_putnbr_fd(t->chaleur_max, 2);
	ft_zeros_to_max(t);
//	ft_putstr_fd("heat fin\n", 2);
}


void ft_init_heat_map(t_info *t)
{
//	ft_putstr_fd("init heat\n", 2);
	int i = 0;
	int j = 0;

	if (!(t->heat_map = (int **)malloc(sizeof(int *) * t->height_map)))
		return ;
	while (i < t->height_map)
	{
		if (!(t->heat_map[i] = (int *)malloc(sizeof(int) * t->width_map)))
			return ;
		i++;
	}
	i = 0;
	while(i < t->height_map)
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
//	ft_putstr_fd("init heat fin\n", 2);
	ft_heat(t);
}

