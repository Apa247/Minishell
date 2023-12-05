/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 18:55:50 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/16 19:26:12 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*arr_join(char **arr)
{
	int		i;
	char	*str;
	char	*aux;

	i = 1;
	str = ft_strdup(arr[0]);
	if (!arr[i])
		return (str);
	while (arr && arr[i])
	{
		aux = str;
		str = ft_strjoin(aux, arr[i]);
		free(aux);
		i++;
	}
	return (str);
}

int	word_count(char *str)
{
	int		i;
	int		wd;
	t_bool	qt;

	if (!str)
		return (0);
	else
	{
		i = 0;
		wd = 1;
		qt = FALSE;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				qt = switch_bool(qt);
				if (qt == TRUE)
					wd++;
			}
			i++;
		}
		return (wd);
	}
}

char	*get_res(char **words, char **env)
{
	char	**aux;
	char	*res;

	aux = exp_words(words, env);
	res = arr_join(aux);
	free_arr(words);
	free_arr(aux);
	return (res);
}

char	*get_trim(char **words)
{
	char	**aux;
	char	*res;

	aux = get_words(words);
	res = arr_join(aux);
	free_arr(words);
	free_arr(aux);
	return (res);
}
