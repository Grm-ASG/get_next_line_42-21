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

static char 	*ft_strchr(const char *s, int c)
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

    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

static void     ft_strcpy(char *dest, const char *src)
{
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
}

char			*ft_strdup(const char *s)
{
    const size_t    s_len = ft_strlen(s);
    char            *new;

    if (!(new = (char *)malloc(s_len + 1)))
        return (NULL);
    ft_strcpy(new, s);
    return (new);
}

static char		*ft_last_str(char **line, t_gnl *temp)
{
	char		*p_lf;

	if (!temp)
		return (NULL);
	if ((*line) != NULL)
		free(*line);
	if (temp->tail == NULL)
		return ((char *)calloc(1,1)); //TODO
	if ((p_lf = ft_strchr(temp->tail, '\n')) == NULL)
	{
		*line = ft_strdup(temp->tail);
		free (temp->start_tail);
		temp->start_tail = NULL;
		temp->tail = NULL;
		return (*line);
	}
	*p_lf = '\0';
	*line = ft_strdup(temp->tail);
	temp->tail = ++p_lf;
	return (*line);
}

static t_gnl	*ft_lst_new(int fd)
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

static t_gnl	*ft_find_lst(int fd, t_gnl **prime)
{
	t_gnl		*temp;

	if (*prime == NULL)
		return ((*prime = ft_lst_new(fd)));
	temp = *prime;
	while (temp->fd != fd && temp->next != NULL)
		temp = temp->next;
	return (temp->fd == fd? temp : (temp->next = ft_lst_new(fd)));
}

static char		*ft_strjoin(char const *s1, char const *s2)
{
    char *new;
    char *ptr;

    if (!(new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
        return (NULL);
    ptr = new;
    while (*s1)
        *ptr++ = *s1++;
    while (*s2)
        *ptr++ = *s2++;
    *ptr = '\0';
    return (new);
}

int             ft_exit(int fd, t_gnl **prime, char **line)
{
    t_gnl       *temp;
    t_gnl       *temp1;

    temp = *prime;
    free(*line);
    if (temp->fd == fd && temp->next == NULL)
    {
        free(temp);
        *prime = NULL;
    }
    else if (temp->fd == fd)
    {
        *prime = temp->next;
        free (temp);
    }
    else
    {
        while (temp->next->fd != fd)
            temp = temp->next;
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
    }
    return (0);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl    *prime;
	char            buf[BUFFER_SIZE + 1];
	int             ret;
	char            *p_lf;
    char            *tmp;

    t_gnl           *t_temp;

    p_lf = NULL;
	if (fd < 0 || !line || !(*line = ft_last_str(line, (t_temp = ft_find_lst(fd, &prime)))))
		return (-1);
	if (t_temp->end)
	    return (ft_exit(fd, &prime, line));
	while (t_temp->tail == NULL && (ret = read(fd, buf, BUFFER_SIZE)))
    {
        if (ret < 0)
            return (-1);
        buf[ret] = '\0';
	    if ((p_lf = ft_strchr(buf, '\n')))
        {
	        *p_lf++ = '\0';
	        if (*p_lf != '\0')
            {
                t_temp->tail = ft_strdup(p_lf);
                t_temp->start_tail = t_temp->tail;
            }
        }
	    tmp = *line;
	    *line = ft_strjoin(*line, buf);
	    free(tmp);
        if (p_lf)
            break;
    }
    if (ret < BUFFER_SIZE && t_temp->tail == NULL)
        t_temp->end = 1;
    return (*line == NULL ? -1 : 1);
}