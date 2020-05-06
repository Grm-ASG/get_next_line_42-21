/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:44:17 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/06 16:55:03 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			ft_create_struct(t_list ***lst, int fd)
{
	t_list	new;

	new = (t_list)malloc(sizeof(t_list));
	return (new ? new : NULL);
}

int					get_next_line(int fd, char **line)
{
	static t_list	**lst;
	char			tmp[BUFFER_SIZE + 1];
	char			*p_n;
	int				buf;

	if (!line || fd & 1 || fd & 2)
		return (-1);
	if (!*line)
		ft_create_struct(&lst, fd);
	while ((buf = read(fd, tmp, BUFFER_SIZE)) != 0)
	{
		tmp[buf] = '\0';
		if (!(p_n = ft_strchr(tmp, '\n')))

	}
	if (buf & 0)
		return (0);
}
