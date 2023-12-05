#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	res;

	a = 0;
	while (s1[a] != 0 && s2[a] != 0 && s1[a] == s2[a])
		a++;
	res = s1[a] - s2[a];
	return (res);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return ((size_t)i);
}
int	ft_wordcount(char const *s, char c)
{
	int	res;
	int	trig;

	res = 0;
	trig = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && trig == 0)
		{
			trig = 1;
			res++;
		}
		else if (*s == c)
			trig = 0;
		s++;
	}
	return (res);
}

char	*ft_word(char const *s, int st, int end)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * (end - st + 1));
	if (ptr == NULL)
		return (0);
	while (st < end)
	{
		ptr[i] = s[st];
		i++;
		st++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	size_t	a;
	int		i;
	char	**split;

	split = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (split == 0)
		return (0);
	index = -1;
	a = 0;
	i = 0;
	while (a <= ft_strlen(s))
	{
		if (s[a] != c && index < 0)
			index = a;
		else if ((s[a] == c || a == ft_strlen(s)) && index >= 0)
		{
			split[i++] = ft_word(s, index, a);
			index = -1;
		}
		a++;
	}
	split[i] = 0;
	return (split);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != 0)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	nlen;
	size_t	b;

	b = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	nlen = ft_strlen(s + start);
	if (nlen < len)
		len = nlen;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (b < len && s[start] != 0)
	{
		ptr[b] = s[start];
		start++;
		b++;
	}
	ptr[b] = '\0';
	return (ptr);
}
