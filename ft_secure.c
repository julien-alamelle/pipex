/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:33 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 11:44:47 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int	ft_open(char *file, int flag, int mode)
{
	int	ret;

	ret = open(file, flag, mode);
	if (ret != -1)
		return (ret);
	perror("open");
	exit(EXIT_FAILURE);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_pipe(int *fd)
{
	if (!pipe(fd))
		return ;
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	ft_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) != -1)
		return ;
	perror("dup2");
	exit(EXIT_FAILURE);
}

void	*ft_malloc(int size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
