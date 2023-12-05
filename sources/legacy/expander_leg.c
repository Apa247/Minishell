/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:40:43 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/09/20 11:12:12 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '\"' || str[0] == '\'')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] == str[0])
				return (1);
			i++;
		}
		if (str[i] == '\0')
			return (2);
	}
	return (0);
}

int	var_search(char **gvars, char *var)
{
	int	pos;

	pos = 0;
	while (gvars[pos])
	{
		if (ft_strnstr(gvars[pos], var, ft_strlen(var)))
			return (pos);
		pos++;
	}
	return (-1);
}

char	*extract_var(char **vars, char *str, int quote)
{
	int		part;
	int		var_pos;
	char	*var;
	char	**s_var;

	part = 1;
	if (quote == 1)
	{
		if  (str[0] == '\"')
			part = 1;
		var = ft_substr(str, 2, ft_strlen(str) - 3);
	}
	else
		var = ft_substr(str, 1, ft_strlen(str) - 1);
	var_pos = var_search(vars, var);
	if (var_pos >= 0)
	{
		s_var = ft_split(vars[var_pos], '=');
		free(var);
		var = ft_strdup(s_var[part]);
		free_arr(s_var);
		return (var);
	}
	else
		return (NULL);
}

char	*expander(t_toolbox *tools, char *str)
{
	if (str[0] == '\'')
		return (ft_substr(str, 1, ft_strlen(str) - 2));
	else if(str[0] == '\"')
		return (extract_var(tools->sort_env, str, 1));
	else
		return (extract_var(tools->sort_env, str, 0));
}
