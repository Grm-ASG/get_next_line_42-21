/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:07:33 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/08 14:56:50 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//TODO check the include libs
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE	150

typedef struct		s_gnl
{
	int				fd;
    int				end;
	char			*tail;
	char			*start_tail;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);

#endif
