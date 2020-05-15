/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:39:08 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/14 18:39:17 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
int					ft_exit_gnl(char *buf, int fd, t_gnl **prime, int result);
char				*ft_strchr_gnl(const char *s, int c);
char				*ft_strdup_gnl(const char *s);
t_gnl				*ft_lst_new_gnl(int fd);
t_gnl				*ft_find_lst_gnl(int fd, t_gnl **prime);

#endif
