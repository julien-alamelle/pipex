/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:46 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 18:43:47 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

#include "pipex.h"

static char	**get_path(char **env)
{
	while (*env && !ft_strcmp(*env, "PATH", '='))
		++env;
	if (!*env)
		return (0);
	return (ft_split((*env) + 5, ':'));
}

static char	*find_path(char **path, char *exe)
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

static void	child(t_data *data, char **env, char **argv)
{
	close(data->fd[0]);
	if (data->current == data->here_doc + 1)
	{
		get_infile(data->fd[1], argv[0], data->here_doc);
		exit(EXIT_SUCCESS);
	}
	ft_dup2(data->fd[1], STDOUT_FILENO);
	ft_dup2(data->fd[2], STDIN_FILENO);
	execve(find_path(data->path, argv[0]), argv, env);
	perror("execve");
	exit(EXIT_FAILURE);
}

static int	check_arg(int ac, char **av)
{
	int	ret;

	if (ac < 3)
	{
		write(2,
			"2 argument required (excluding executable name and here_doc)\n",
			61);
		exit(EXIT_FAILURE);
	}
	ret = ft_strcmp(av[1], "here_doc", 0);
	if (ac == 3 && ret)
	{
		write(2,
			"2 argument required (excluding executable name and here_doc)\n",
			61);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.here_doc = check_arg(argc, argv);
	data.path = get_path(env);
	data.current = data.here_doc;
	data.fd[0] = 0;
	while (++data.current < argc - 1)
	{
		data.fd[2] = data.fd[0];
		ft_pipe(data.fd);
		data.pid = ft_fork();
		if (!data.pid)
			child(&data, env, ft_split(argv[data.current], ' '));
		else
		{
			close(data.fd[1]);
			close(data.fd[2]);
		}
	}
	copy_content(data.fd[0], argv[data.current], data.here_doc);
	while (wait(0) >= 0)
		;
	return (0);
}
