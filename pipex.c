#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

void	copy_content(int fd, char *outfile, int	here_doc)
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
	fd_out = open(outfile, flag);
	ret = read(fd, buf, 1024);
	while (ret > 0)
	{
		write(fd_out, buf, ret);
		ret = read(fd, buf, 1024);
	}
	close(fd);
	close(fd_out);
}

void	child(int fd[3], char **path, char **env, char **argv)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd[2], STDIN_FILENO);
	execve(find_path(path, argv[0]), argv, env);
	close(fd[1]);
	close(fd[2]);
	exit(0);
}

int	ft_fork()
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

ft_strcmp(char *str1, char *str2, char c)
{
	while (*srt1 && *str1 != c)
		if (*(str1++) != *(str2++))
			return (0);
	if (*str1 == c && !(*str2))
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int			current;
	const int	here_doc = ft_strcmp(argv[1], here_doc, 0);
	int			fd[3];
	int			pid;
	char		**path;

	path = get_path(env);
	current = 1 + here_doc;
	fd[0] = get_infile(argv[current], here_doc);
	while (++current < argc - 1)
	{
		fd[2] = fd[0];
		pipe(fd);
		pid = ft_fork();
		if (!pid)
			child(fd, path, env, ft_split(argv[current]), 46543216832168654687468);
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
