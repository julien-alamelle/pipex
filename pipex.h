/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:51 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 18:25:07 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	int		current;
	int		here_doc;
	int		fd[3];
	int		pid;
	char	**path;
}	t_data;

char	**ft_split(char *str, char c);
char	*ft_strjoin(char *str1, char *str2);
int		ft_strcmp(char *str1, char *str2, char c);

int		ft_open(char *file, int flag, int mode);
int		ft_fork(void);
void	ft_pipe(int *fd);
void	ft_dup2(int oldfd, int newfd);
void	*ft_malloc(int size);

void	copy_content(int fd, char *outfile, int here_doc);
void	get_infile(int fd, char *file, int here_doc);

#endif
