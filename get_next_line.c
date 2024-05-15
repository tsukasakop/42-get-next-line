/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:36:07 by tkondo            #+#    #+#             */
/*   Updated: 2024/05/16 02:26:46 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static bool	pack(char **p_store, char *s)
{
	char	*bk;

	if (*p_store == NULL)
	{
		*p_store = ft_substr("", 0, 0);
		if (*p_store == NULL)
			return (false);
	}
	bk = *p_store;
	*p_store = ft_strjoin(*p_store, s);
	free(bk);
	return (*p_store != NULL);
}

static bool	read_and_pack(char **p_store, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_bytes;

	while (*p_store == NULL || ft_strchr(*p_store, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (false);
		buf[read_bytes] = '\0';
		if (!pack(p_store, buf))
			return (false);
		if (read_bytes < BUFFER_SIZE)
			break ;
	}
	return (true);
}

static char	*extract_line(char **p_store)
{
	char	*p_nl;
	char	*p_end;
	char	*origin;
	char	*line;

	p_nl = ft_strchr(*p_store, '\n');
	p_end = *p_store + ft_strlen(*p_store);
	origin = *p_store;
	*p_store = NULL;
	if (p_nl == NULL)
		line = ft_substr(origin, 0, p_end - origin);
	else
	{
		line = ft_substr(origin, 0, p_nl - origin + 1);
		*p_store = ft_substr(origin, p_nl - origin + 1, p_end - p_nl);
		if (line == NULL || *p_store == NULL)
		{
			free(line);
			line = NULL;
			free(*p_store);
			*p_store = NULL;
		}
	}
	free(origin);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*read_s;

	if (!read_and_pack(&read_s, fd))
	{
		free(read_s);
		read_s = NULL;
		return (NULL);
	}
	return (extract_line(&read_s));
}
