/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:07:33 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/06 16:43:59 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//TODO check the include libs
# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE	10

typedef struct		s_list
{
	int				fd;
	char			flag_done;
	char			*last;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);

#endif
