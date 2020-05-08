#include <stdio.h>
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

static t_list		*ft_lstnew(int fd)
{
	t_list	*new;

	if ((new = (t_list *)malloc(sizeof(t_list))))
	{
		new->fd = fd;
		new->tail = NULL;
		new->next = NULL;
	}
	return (new);
}

static t_list		*ft_find_lst(t_list **prime, int fd)
{
	t_list *tmp;

	tmp = (*prime);
	if (*prime == NULL)
		return (((*prime) = ft_lstnew(fd)));
	while (tmp->fd != fd && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp->fd == fd ? tmp : (tmp->next = ft_lstnew(fd)));
}

static size_t		ft_strlen(const char *s)
{
	const char	*p = s;

	while (*p)
		++p;
	return (p - s);
}

static void			*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *dp;

	dp = dest;
	while (n-- > 0)
		*dp++ = *(char *)(src++);
	return (dest);
}

static char			*ft_strchr(char *s, int c)
{
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static char			*ft_strdup(char *s)
{
	const size_t	len = ft_strlen(s);
	char *const		res = malloc(len + 1);

	if (!res)
		return (NULL);
	return (ft_memcpy(res, s, len + 1));
}

static void			*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	if (!(ptr = malloc(size * nmemb)))
		return (NULL);
	i = -1;
	while (++i < nmemb * size)
		ptr[i] = '\0';
	return ((void *)ptr);
}

static void			ft_strcpy(char *dest, char *src)
{
	if (!dest)
		return ;
	while (*src)
		*dest++ = *src++;
	*dest++ = *src++;
}

int				ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
		if (*s1++ != *s2++)
			return (*--s1 - *--s2);
	return (0);
}

static char			*ft_strcpy_mod(char **line, char **src, int ret[][2])
{
	char	*p_n;
	char	*tmp;

	if ((*src) == NULL)
		return (ft_calloc(1, 1));
	if (!(p_n = ft_strchr((*src), '\n')))
		ft_strcpy(((*line) = malloc(ft_strlen(*src) + 1)), *src);
	else
	{
		(*src)[p_n - (*src)] = '\0';
		ft_strcpy(((*line) = malloc(ft_strlen(*src) + 1)), *src);
		tmp = (*src);
		if (!((*src) = ft_strdup(++p_n)))
			return (NULL);
		free(tmp);
		if (!(p_n = ft_strchr((*src), '\n')))
			(*ret)[1] = 0;
		else
			(*ret)[1] = 1;
		if (!ft_strcmp((*line), (*src)))
			free (*src);
	}
	return (*line);
}

static char			*ft_strjoin(char const *s1, char const *s2)
{
	const int 	len_s1 = (s1? ft_strlen(s1) : 0);
	char *new;
	const char *tmp = s1;
	char *ptr;

	if (!(new = (char *)malloc(len_s1 + ft_strlen(s2) + 1)))
		return (NULL);
	ptr = new;
	if (s1)
	{
		while (*s1)
			*ptr++ = *s1++;
	}
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	if (tmp)
		free((char *)tmp);
	return (new);
}

static char			*ft_line_sep(char buf[], char *p_n, char **tail, int ret)
{
	printf("buf		= %s\n", buf);
	buf[p_n - buf] = '\0';
	if (tmp->tail != NULL && !(tmp->tail = ft_strjoin(tmp->tail, &buf[p_n - buf + 1])))
		return (-1);
	else if (!(tmp->tail = ft_strdup(&buf[p_n - buf + 1])))
		return (-1);
	*line = ft_strjoin((*line), buf);
	printf("line	= %s\n", (*line));
	printf("last	= %s\n", tmp->tail);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*prime;
	t_list			*tmp;
	char			buf[BUFFER_SIZE + 1];
	char			*p_n;
	int				ret[2];

	ret[1] = 0;
	if (!(fd == 0 || fd > 2) || !(tmp = ft_find_lst(&prime, fd)) ||
		!((*line) = ft_strcpy_mod(line, &tmp->tail, &ret)))
		return (-1);
	if (!ret[1])
		while ((ret[0] = read(fd, buf, BUFFER_SIZE)) != 0)
		{
			buf[ret[0]] = '\0';
			if ((p_n = ft_strchr(buf, '\n')))
			{
				if (!(*line = ft_line_sep(buf, p_n, &tmp->tail, ret[0])))
					return (-1);
				break;
			}
			else
				*line = ft_strjoin((*line), buf);
		}
	return (!ret[0] && !ret[1] ? 0 : 1);
}
