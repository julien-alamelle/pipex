/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:28:40 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 18:28:42 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "pipex.h"

void	copy_content(int fd, char *outfile, int here_doc)
{
	int		fd_out;
	char	buf[1024];
	int		ret;
	int		flag;

	flag = O_WRONLY | O_CREAT;
	if (here_doc)
		flag = flag | O_APPEND;
	else
		flag = flag | O_TRUNC;
	fd_out = ft_open(outfile, flag, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	ret = read(fd, buf, 1024);
	while (ret > 0)
	{
		write(fd_out, buf, ret);
		ret = read(fd, buf, 1024);
	}
	close(fd);
	close(fd_out);
}

static int	gnl2(char *buf, int *start, int *end, int *loopfd)
{
	int	i;

	if (*start == *end)
	{
		*end = read(loopfd[1], buf, 1024);
		*start = 0;
	}
	if (*start >= *end)
		*loopfd = 0;
	i = 0;
	while (*start + i < *end && buf[*start + i] != '\n')
		++i;
	if (*start + i < *end && buf[*start + i] == '\n')
	{
		++i;
		*loopfd = 0;
	}
	return (i);
}

static char	*gnl(int fd, char *buf, int *start, int *end)
{
	char	*ret;
	char	*tmp;
	int		loopfd[2];
	int		i;
	char	cheat;

	buf[1024] = 0;
	ret = ft_malloc(1);
	ret[0] = 0;
	*loopfd = 1;
	loopfd[1] = fd;
	while (*loopfd)
	{
		i = gnl2(buf, start, end, loopfd);
		cheat = buf[*start + i];
		buf[*start + i] = 0;
		tmp = ft_strjoin(ret, buf + (*start));
		*start += i;
		buf[*start] = cheat;
		free(ret);
		ret = tmp;
	}
	if (!(*ret || fd))
		write(2, "warning, here_doc reach end-of-file\n", 36);
	return (ret);
}

void	get_infile(int fd, char *file, int here_doc)
{
	int		fd2;
	char	buf[1025];
	char	*line;
	int		start;
	int		end;

	fd2 = 0;
	if (!here_doc)
		fd2 = (ft_open(file, O_RDONLY, 0));
	end = 1024;
	start = 1024;
	line = gnl(fd2, buf, &start, &end);
	while (*line && (!ft_strcmp(line, file, '\n') || fd2))
	{
		here_doc = 0;
		while (line[here_doc])
			++here_doc;
		write(fd, line, here_doc);
		free(line);
		line = gnl(fd2, buf, &start, &end);
	}
	free(line);
	close(fd2);
}
