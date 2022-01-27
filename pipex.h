/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:51 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 11:45:36 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	**ft_split(char *str, char c);

int		ft_open(char *file, int flag, int mode);
int		ft_fork(void);
void	ft_pipe(int *fd);
void	ft_dup2(int oldfd, int newfd);
void	*ft_malloc(int size);

void	copy_content(int fd, char *outfile, int here_doc);
char	*gnl(char *buf, int *start, int *end);
char	*ft_strjoin(char *str1, char *str2);
int		ft_strcmp(char *str1, char *str2, char c);

#endif
