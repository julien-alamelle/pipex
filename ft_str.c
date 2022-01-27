#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "pipex.h"

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
	fd_out = ft_open(outfile, flag);
	ret = read(fd, buf, 1024);
	while (ret > 0)
	{
		write(fd_out, buf, ret);
		ret = read(fd, buf, 1024);
	}
	close(fd);
	close(fd_out);
}

int	ft_strcmp(char *str1, char *str2, char c)
{
	while (*str1 && *str1 != c)
		if (*(str1++) != *(str2++))
			return (0);
	if (*str1 == c && !(*str2))
		return (1);
	return (0);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str1[i])
		++i;
	while (str2[j])
		++j;
	ret = ft_malloc(i + j + 1);
	ret[i + j] = 0;
	while (j--)
		ret[i + j] = str2[j];
	while (i--)
		ret[i] = str1[i];
	return (ret);
}

static int	gnl2(char *buf, int *start, int *end, int *loop)
{
	int	i;

	if (*start == *end)
	{
		*end = read(0, buf, 1024);
		*start = 0;
	}
	if (*start >= *end)
		*loop = 0;
	i = 0;
	while (*start + i < *end && buf[*start + i] != '\n')
		++i;
	if (*start + i < *end && buf[*start + i] == '\n')
	{
		++i;
		*loop = 0;
	}
	return (i);
}

char	*gnl(char *buf, int	*start, int *end)
{
	char	*ret;
	char	*tmp;
	int		loop;
	int		i;
	char	cheat;

	buf[1024] = 0;
	ret = ft_malloc(1);
	ret[0] = 0;
	loop = 1;
	while (loop)
	{
		i = gnl2(buf, start, end, &loop);
		cheat = buf[*start + i];
		buf[*start + i] = 0;
		tmp = ft_strjoin(ret, buf + (*start));
		*start += i;
		buf[*start] = cheat;
		free(ret);
		ret = tmp;
	}
	if (!(*ret))
		write(2, "warning, here_doc reach end-of-file\n", 36);
	return (ret);
}
