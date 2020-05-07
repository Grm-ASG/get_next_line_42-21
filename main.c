/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:01:27 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/06 16:08:43 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // for open
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int				main(int argc, char **argv)
{
	int		i;
	int		fd;
	char	*str;

	if (argc != 2)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while(get_next_line(fd, &str))
	{
		i++;
		printf("string[%d] = %s \n", i,  str);
	}
	return (0);
}
