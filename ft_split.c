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
