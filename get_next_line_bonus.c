/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:36:07 by tkondo            #+#    #+#             */
/*   Updated: 2024/05/16 06:52:40 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static char	*nullize_free(char **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

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
		if (read_bytes == 0 && *p_store == NULL)
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
	if (p_nl == NULL || p_nl + 1 == p_end)
		line = ft_substr(origin, 0, p_end - origin);
	else
	{
		line = ft_substr(origin, 0, p_nl - origin + 1);
		*p_store = ft_substr(origin, p_nl - origin + 1, p_end - p_nl);
		if (line == NULL || *p_store == NULL)
		{
			nullize_free(&line);
			nullize_free(p_store);
		}
	}
	free(origin);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*read_s[MAX_FILE_DESCRIPTOR + 1];

	if (fd < 0 || fd > MAX_FILE_DESCRIPTOR)
		return (NULL);
	if (!read_and_pack(read_s + fd, fd))
		return (nullize_free(read_s + fd));
	return (extract_line(read_s + fd));
}
