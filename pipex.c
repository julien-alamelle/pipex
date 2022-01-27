/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:46 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 11:47:14 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

#include "pipex.h"

char	**get_path(char **env)
{
	while (*env && !ft_strcmp(*env, "PATH", '='))
		++env;
	if (!*env)
		return (0);
	return (ft_split((*env) + 5, ':'));
}

char	*find_path(char **path, char *exe)
{
	char	*tmp;

	if (!path)
		return (exe);
	if (!access(exe, X_OK))
		return (exe);
	while (*path)
	{
		tmp = ft_strjoin(*path, exe);
		if (!access(tmp, X_OK))
			return (tmp);
		free(tmp);
		++path;
	}
	return (exe);
}

int	get_infile(char	*file, int here_doc)
{
	int		fd[2];
	char	buf[1025];
	char	*line;
	int		start;
	int		end;

	if (!here_doc)
		return (ft_open(file, O_RDONLY, 0));
	end = 1024;
	start = 1024;
	ft_pipe(fd);
	line = gnl(buf, &start, &end);
	while (*line && !ft_strcmp(line, file, '\n'))
	{
		here_doc = 0;
		while (line[here_doc])
			++here_doc;
		write(fd[1], line, here_doc);
		free(line);
		line = gnl(buf, &start, &end);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

void	child(int fd[3], char **path, char **env, char **argv)
{
	close(fd[0]);
	ft_dup2(fd[1], STDOUT_FILENO);
	ft_dup2(fd[2], STDIN_FILENO);
	execve(find_path(path, argv[0]), argv, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	int			current;
	const int	here_doc = ft_strcmp(argv[1], "here_doc", 0);
	int			fd[3];
	int			pid;
	char		**path;

	path = get_path(env);
	current = 1 + here_doc;
	fd[0] = get_infile(argv[current], here_doc);
	while (++current < argc - 1)
	{
		fd[2] = fd[0];
		ft_pipe(fd);
		pid = ft_fork();
		if (!pid)
			child(fd, path, env, ft_split(argv[current], ' '));
		else
		{
			close(fd[1]);
			close(fd[2]);
			wait(0);
		}
	}
	copy_content(fd[0], argv[current], here_doc);
	return (0);
}
