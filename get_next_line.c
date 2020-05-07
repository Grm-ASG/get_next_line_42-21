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

static void			ft_clear_lst(t_list **lst)
{
	t_list	*tmp;
	if (*lst)
		while ((*lst)->next)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp);
		}
}

static t_list		*ft_check_list(int fd, t_list **lst)
{
	t_list	*tmp;

	if (*lst)
	{
		tmp = (*lst);
		while ((tmp->fd != fd) && tmp->next)
			tmp = tmp->next;
		if (tmp->fd == fd)
			return (*lst);
		tmp->next = (t_list *)malloc(sizeof(t_list));
		if ((tmp->next) == NULL)
		{
			ft_clear_lst(lst);
			return (NULL);
		}
		tmp->next->fd = fd;
		tmp->next->flag_done = 0;
		tmp->next->next = NULL;
		tmp->next->last = NULL;
		return (*lst);
	}
	*lst = (t_list *)malloc(sizeof(t_list));
	if (*lst == NULL)
		return (NULL);
	tmp = *lst;
	tmp->fd = fd;
	tmp->next = NULL;
	tmp->last = NULL;
	return (*lst);
}

#include <stdio.h>

char				*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

size_t				ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	const int	len_s1 = ft_strlen(s1);
	const int	len_s2 = ft_strlen(s2);
	char		*new;
	char		*ptr;

	if (!(ptr = new = (char *)malloc(len_s1 + len_s2 + 1)))
		return (NULL);
	if (s1)
		while (*s1)
			*ptr++ = *s1++;
	if (s2)
		while (*s2)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (new);
}

void		*ft_memset(void *s, int c, size_t n)
{
	unsigned char *p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = c;
	return (s);
}

void			*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size * nmemb)))
		return (NULL);
	return (ft_memset(ptr, '\0', size * nmemb));
}

size_t				ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	if (!src || !dest)
		return (0);
	if (size)
	{
		while (++i < size - 1 && src[i] != '\0')
			dest[i] = src[i];
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*new;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *)s);
	if (s_len < start + 1)
		return ((char *)ft_calloc(1, 1));
	s += start;
	s_len = ft_strlen((char *)s);
	s_len = s_len > len ? len + 1 : s_len + 1;
	ft_strlcpy((new = (char *)malloc(s_len)), s, s_len);
	return (new);
}

int					get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_list			*ptr_lst;
	char			tmp[BUFFER_SIZE + 1];
	char			*p_n;
	int				buf;

	if (fd == 1 || fd == 2 || fd < 0)
		return (-1);
	if (!lst || !*line)
		if (!(ptr_lst = lst = ft_check_list(fd, &lst)))
			return (-1);
	while (ptr_lst->fd != fd)
		ptr_lst = ptr_lst->next;
	*line = NULL;
	if (lst->last && !(lst->flag_done))
		*line = ft_strjoin(*line, lst->last);
	if (!(lst->flag_done))
		while ((buf = read(fd, tmp, BUFFER_SIZE)) != 0)
		{
			tmp[buf] = '\0';
			p_n = ft_strchr(tmp, '\n');
			if (p_n)
				tmp[p_n - tmp] = '\0';
			*line = ft_strjoin(*line, tmp);
			if (p_n)
				break;
		}
	if (buf == 0 && lst->last)
		lst->flag_done = 1;
	if (lst->flag_done)
		return (0);
	if (p_n)
		lst->last = (char *)ft_substr(++p_n, 0, BUFFER_SIZE + 1);
	return (1);
}
