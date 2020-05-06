/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 10:44:17 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/06 14:55:59 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# define BUFFER_SIZE	10

int				get_next_line(int fd, char **line)
{
	int		buf;

	if (!line || fd & 1 || fd & 2)
		return (-1);
	while ((buf = read(fd, BUFFER_SIZE, O_RDONLY)) != 0)
	{
	}
	if (buf & 0)
		return (0);
}
