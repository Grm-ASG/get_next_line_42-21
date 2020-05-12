/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imedgar <imedgar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 20:09:52 by imedgar           #+#    #+#             */
/*   Updated: 2020/05/12 20:20:50 by imedgar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (unsigned char)c)
			return ((char *)--s);
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void		ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char		*ft_strdup(const char *s)
{
	const size_t	s_len = ft_strlen(s);
	char			*new;

	if (!(new = (char *)malloc(s_len + 1)))
		return (NULL);
	ft_strcpy(new, s);
	return (new);
}

t_gnl		*ft_lst_new(int fd)
{
	t_gnl		*new;

	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->tail = NULL;
	new->start_tail = NULL;
	new->next = NULL;
	return (new);
}
