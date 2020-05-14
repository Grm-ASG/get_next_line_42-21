/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:22:48 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/14 16:23:28 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_last_str(char **line, t_gnl *temp)
{
	char		*p_lf;
	char		*new;

	if (temp->tail == NULL)
	{
		if (!(new = (char *)malloc(1)))
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	if ((p_lf = ft_strchr(temp->tail, '\n')) == NULL)
	{
		if (!(*line = ft_strdup(temp->tail)))
			return (NULL);
		free(temp->start_tail);
		temp->start_tail = NULL;
		temp->tail = NULL;
		return (*line);
	}
	*p_lf++ = '\0';
	if (!(*line = ft_strdup(temp->tail)))
		return (NULL);
	temp->tail = p_lf;
	return (*line);
}

static int		get_line_sup(char *buf, char **p_lf, t_gnl *t_temp, char **line)
{
	if (((*p_lf) = ft_strchr(buf, '\n')))
	{
		(**p_lf) = '\0';
		++(*p_lf);
		if (!(t_temp->tail = ft_strdup(*p_lf)))
			return (-1);
		t_temp->start_tail = t_temp->tail;
	}
	t_temp->line_back_up = *line;
	if (!(*line = ft_strjoin(*line, buf)))
		return (-1);
	free(t_temp->line_back_up);
	return (0);
}

static int		get_line(int fd, char **line, t_gnl *t_temp, t_gnl **prime)
{
	char			*buf;
	int				ret;
	int				res_from_sup;
	char			*p_lf;

	p_lf = NULL;
	ret = 0;
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (ft_exit(buf, fd, prime, -1));
	while (!p_lf && !t_temp->tail && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (ft_exit(buf, fd, prime, -1));
		buf[ret] = '\0';
		res_from_sup = get_line_sup(buf, &p_lf, t_temp, line);
		if (res_from_sup == -1)
			return (ft_exit(buf, fd, prime, -1));
	}
	if (ret < BUFFER_SIZE && t_temp->tail == NULL)
		return (ft_exit(buf, fd, prime, 0));
	free(buf);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*prime;
	t_gnl			*t_temp;
	char			check[1];

	if (BUFFER_SIZE < 1 ||
		!line || fd < 0 ||
		((read(fd, check, 0)) < 0))
		return (-1);
	if (!(t_temp = ft_find_lst(fd, &prime)) ||
		!(*line = ft_last_str(line, t_temp)))
		return (ft_exit(NULL, fd, &prime, -1));
	return (get_line(fd, line, t_temp, &prime));
}
