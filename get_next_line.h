/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:07:33 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/12 20:23:08 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_gnl
{
	int				fd;
	int				end;
	char			*tail;
	char			*start_tail;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
char				*ft_strchr(const char *s, int c);
size_t				ft_strlen(const char *s);
void				ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *s);
t_gnl				*ft_lst_new(int fd);

#endif
