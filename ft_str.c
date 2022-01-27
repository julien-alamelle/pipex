/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 11:26:42 by jalamell          #+#    #+#             */
/*   Updated: 2022/01/27 12:45:03 by jalamell         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* ********************************** */
/* mode = 0 : count number of words   */
/* mode = 1 : count size od word      */
/* ********************************** */

static int	ft_count(unsigned char *str, char c, char mode)
{
	int				count;

	count = 0;
	while (str[0] && !(mode && str[0] == c))
	{
		if (mode)
			++count;
		else
		{
			if ((!str[1] || str[1] == c) && str[0] != c)
				++count;
		}
		++str;
	}
	return (count);
}

static void	ft_fill_ret(char **ret, unsigned char *str, char c, int nb_word)
{
	int		size;
	int		j;
	int		i;

	i = -1;
	while (++i < nb_word)
	{
		while (*str == c)
			++str;
		size = ft_count(str, c, 1);
		if (c == ':')
			++size;
		*ret = ft_malloc((size + 1) * sizeof(char *));
		j = -1;
		while (++j < size)
			(*ret)[j] = str[j];
		if (c == ':')
			(*ret)[j - 1] = '/';
		(*ret)[j] = 0;
		str += size;
		++ret;
	}
}

char	**ft_split(char *str, char c)
{
	int		nb_word;
	char	**ret;

	nb_word = ft_count((unsigned char *)str, c, 0);
	ret = ft_malloc((nb_word + 1) * sizeof(char *));
	ret[nb_word] = 0;
	ft_fill_ret(ret, (unsigned char *)str, c, nb_word);
	return (ret);
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
