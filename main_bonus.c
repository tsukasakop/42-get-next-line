/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:35:21 by tkondo            #+#    #+#             */
/*   Updated: 2024/05/16 10:20:09 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

char	*exec_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	printf("fd(%d): %s\n", fd, line);
	free(line);
	return (line);
}

void	exec_gnl_in_turns(int fd1, int fd2)
{
	int		cnt;
	char	*line;
	int		fd;

	cnt = 0;
	line = exec_gnl(fd1);
	cnt++;
	if (print_err())
		return ;
	while (line)
	{
		fd = (cnt % 2 == 0) * fd1 + (cnt % 2 == 1) * fd2;
		line = exec_gnl(fd);
		cnt++;
		if (print_err())
			return ;
	}
}

int	main(void)
{
	char	*p1;
	char	*p2;
	int		fd1;
	int		fd2;

	p1 = "test.txt";
	p2 = "text2.txt";
	printf("BUFFER_SIZE=%d\n", BUFFER_SIZE);
	fd1 = open(p1, O_RDONLY);
	printf("- open '%s' on fd(%d)\n", p1, fd1);
	fd2 = open(p2, O_RDONLY);
	printf("- open '%s' on fd(%d)\n", p2, fd2);
	exec_gnl_in_turns(fd1, fd2);
	close(fd1);
	printf("- close '%s' on fd(%d)\n", p1, fd1);
	close(fd2);
	printf("- close '%s' on fd(%d)\n", p2, fd2);
	system("leaks -q a.out");
}
