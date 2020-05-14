/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:07:33 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/14 16:05:29 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_gnl
{
	int				fd;
	char			*tail;
	char			*start_tail;
	char			*line_back_up;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
int					ft_exit(char *buf, int fd, t_gnl **prime, int result);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
t_gnl				*ft_lst_new(int fd);
t_gnl				*ft_find_lst(int fd, t_gnl **prime);

#endif
