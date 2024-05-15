/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:35:21 by tkondo            #+#    #+#             */
/*   Updated: 2024/05/16 03:18:23 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static bool	print_err(void)
{
	if (errno == 0)
		return (false);
	printf("- error(%d): %s\n", errno, strerror(errno));
	errno = 0;
	return (true);
}

bool	test(char *path)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(path, O_RDONLY);
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	printf("- open '%s' on fd(%d)\n", path, fd);
	i = 0;
	line = get_next_line(fd);
	printf("%d: %s\n", i, line);
	while (line)
	{
		i++;
		line = get_next_line(fd);
		printf("%d: %s\n", i, line);
		if (print_err())
			break ;
	}
	close(fd);
	printf("- close '%s' on fd(%d)\n", path, fd);
	return (true);
}

int	main(void)
{
	bool	res;

	res = true;
	res = (res && test("test.txt"));
	return (!res);
}
