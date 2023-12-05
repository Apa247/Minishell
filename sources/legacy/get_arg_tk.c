/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_tk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:49:58 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/14 16:05:00 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_arg(char *input, int st, int end)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			st = i;
			i++;
			while (input[i] != input[st] && input[i])
				i++;
			if (i == 0)
				return (NULL);
			else
				return (ft_substr(input, st, i - st));
		}
		i++;
	}
	return (NULL);
}

t_token	get_token(char *input, int st, int end)
{
	int	i;

	i = 0;
	while (input[st])
	{
		if (input[st] == '|')
			return (1);
		if (input[st] == '<')
		{
			if (input[st + 1] == '<')
				return (3);
			else
				return (2);
		}
		if (input[st] == '>')
		{
			if (input[st + 1] == '>')
				return (5);
			else
				return (4);
		}
		st++;
	}
	return (0);
}
