/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmangili <rmangili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 14:39:29 by rmangili          #+#    #+#             */
/*   Updated: 2015/01/04 00:38:37 by rmangili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int x)
{
	char *s3;

	s3 = ft_strjoin(s1, s2);
	if (x & 1)
		free(s1);
	if (x & 2)
		free(s2);
	return (s3);
}

static int	buf_split(char *buf, char **line)
{
	char	*endl_ptr;

	if (buf[0] == '\0')
		return (1);
	if ((endl_ptr = ft_strchr(buf, '\n')))
		*endl_ptr = '\0';
	if (*line == NULL)
		*line = ft_strdup(buf);
	else
		*line = ft_strjoinfree(*line, buf, 1);
	if (endl_ptr)
		ft_strcpy(buf, endl_ptr + 1);
	return (endl_ptr == NULL);
}

int			get_next_line(const int fd, char **line)
{
	int				ret_read;
	static char		*buf = NULL;

	*line = NULL;
	if (buf == NULL)
		if (!(buf = ft_memalloc(BUFF_SIZE + 1)))
			return (1);
	while (buf_split(buf, line))
	{
		if (!(ret_read = read(fd, buf, BUFF_SIZE)))
		{
			if (*line != NULL)
				return (1);                  //gerer le cas ou pas de \n dans le fichier
			return (0);
		}
		if (ret_read == -1)
			return (-1);
		buf[ret_read] = '\0';
	}
	return (1);
}