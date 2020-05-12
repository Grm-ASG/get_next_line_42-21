/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:01:27 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/12 23:20:15 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int				main(int argc, char **argv)
{
	int		fd;
	int		j;
	char	*str;

	str = NULL;
	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	while ((j = get_next_line(fd, &str)))
	{
		if (j < 0)
			break ;
		printf("%s\n", str);
		free(str);
	}
	free(str);
	return (0);
}
