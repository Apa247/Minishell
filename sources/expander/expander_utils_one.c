/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:21:11 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/22 17:49:11 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exp_count(char *str)
{
	int	i;
	int	wd;

	if (!str)
		return (0);
	i = 0;
	wd = 1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] == '$' && str[i])
				i++;
			wd++;
		}
		i++;
	}
	if (wd == 0)
		wd = 1;
	return (wd);
}

char	*expnd(char *str, char **env)
{
	char	*aux;
	char	**r_var;
	int		i;

	aux = ft_strjoin(str, "=");
	free(str);
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], aux, ft_strlen(aux)))
		{
			r_var = ft_split(env[i], '=');
			free(aux);
			aux = ft_strdup(r_var[1]);
			free_arr(r_var);
			return (aux);
		}
		i++;
	}
	free(aux);
	aux = malloc(sizeof(char) * 1);
	aux[0] = 0;
	return (aux);
}

int	get_dollar(char *str, int *it, char **arr, char **env)
{
	int		j;

	j = 0;
	while (str[it[0]] == '$' && str[it[0]])
		it[0]++;
	while (str[it[0] + j])
	{
		if (str[it[0] + j] == '$' || str[it[0] + j] == ' ')
			break ;
		j++;
	}
	arr[it[2]] = expnd(ft_substr(str, it[0], j), env);
	it[0] += j;
	it[2]++;
	return (it[0]);
}

int	get_uncuote(char *str, int *it, char **arr)
{
	it[1] = 0;
	while (str[it[0] + it[1]] != '$' && str[it[0] + it[1]])
		it[1]++;
	arr[it[2]] = ft_substr(str, it[0], it[1]);
	it[2]++;
	it[0] += it[1];
	return (it[0]);
}

char	*exp_word(char *str, char **env)
{
	char	**arr;
	int		it[3];
	char	*res;

	it[0] = 0;
	it[1] = 0;
	it[2] = exp_count(str);
	arr = ft_calloc(sizeof(char *), (it[2] + 2));
	if (!arr)
		return (NULL);
	it[2] = 0;
	while (str[it[0]])
	{
		if (str[it[0]] == '$')
			it[0] = get_dollar(str, it, arr, env);
		else
			it[0] = get_uncuote(str, it, arr);
	}
	arr[it[2]] = 0;
	res = arr_join(arr);
	free_arr(arr);
	return (res);
}
