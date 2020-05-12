/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 01:10:16 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/13 01:10:18 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1] != '\0')
		++len_s1;
	while (s2[len_s2] != '\0')
		++len_s2;
	if (!(new = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	ptr = new;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (new);
}

static int		get_line_sup(char *buf, char **p_lf, t_gnl *t_temp, char **line)
{
	if (((*p_lf) = ft_strchr(buf, '\n')))
	{
		(**p_lf) = '\0';
		++(*p_lf);
		if ((**p_lf) != '\0')
		{
			if (!(t_temp->tail = ft_strdup(*p_lf)))
				return (-1);
			t_temp->start_tail = t_temp->tail;
		}
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
	ret = BUFFER_SIZE;
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (ft_exit(buf, fd, prime, -1));
	while (!p_lf && t_temp->tail == NULL && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret < 0)
			return (ft_exit(buf, fd, prime, -1));
		buf[ret] = '\0';
		res_from_sup = get_line_sup(buf, &p_lf, t_temp, line);
		if (res_from_sup == -1)
			return (ft_exit(buf, fd, prime, -1));
	}
	if (ret == 0 && *line[0] == '\0')
		return (ft_exit(buf, fd, prime, 0));
	free(buf);
	if (ret < BUFFER_SIZE && t_temp->tail == NULL)
		t_temp->end = 1;
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*prime;
	t_gnl			*t_temp;
	char			check[1];

	if (!line || fd < 0 || ((read(fd, check, 0)) < 0))
		return (-1);
	if (!(t_temp = ft_find_lst(fd, &prime)) ||
		!(*line = ft_last_str(line, t_temp)))
		return (ft_exit(NULL, fd, &prime, -1));
	if (t_temp->end && *line[0] == '\0')
		return (ft_exit(NULL, fd, &prime, 0));
	return (get_line(fd, line, t_temp, &prime));
}
