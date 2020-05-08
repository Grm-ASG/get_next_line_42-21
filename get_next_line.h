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

typedef struct		s_list
{
	int				fd;
	char			*tail;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
static char			*ft_strcpy_mod(char **line, char **src, int ret[][2]);
static char			*ft_strjoin(char const *s1, char const *s2);
static char			*ft_line_sep(char buf[], char *p_n, char **tail, int ret);
static t_list		*ft_lstnew(int fd);
static t_list		*ft_find_lst(t_list **prime, int fd);
static size_t		ft_strlen(const char *s);
static void			*ft_memcpy(void *dest, const void *src, size_t n);
static char			*ft_strchr(char *s, int c);
static char			*ft_strdup(char *s);
static void			*ft_calloc(size_t nmemb, size_t size);
static void			ft_strcpy(char *dest, char *src);
static int			ft_strcmp(char *s1, char *s2);

#endif
