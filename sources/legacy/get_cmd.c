/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 12:28:58 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/14 16:00:05 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_white_space(char a)
{
	if (a == '\t' || a == '\n' || a == '\v' ||
		   	a == '\f' || a == '\r' || a == ' ')
		return (1);
	else
		return (0);
}

int	word_count(char *s_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (is_white_space(s_cmd[i]) != 0)
		i++;
	while (s_cmd[i])
	{
		if (is_white_space(s_cmd[i] == 1))
			count++;
		i++;
	}
	return (count);
}

char	*wordle(char *s_cmd, int st)
{
	int		end;
	char	*word;

	end = st;
	while (is_white_space(s_cmd[end]) == 0)
		end++;
	word = ft_substr(s_cmd, st, end - st);
	return (word);
}

char	**cmd_split(char* s_cmd)
{
	int		wds;
	int		end;
	int		i;
	char	**c_cmd;

	end = 0;
	i = 0;
	wds = word_count(s_cmd);
	c_cmd == malloc(sizeof(char *) * wds + 1);
	if (!c_cmd)
		return (NULL);
	while (s_cmd[end])
	{
		if (is_white_space(s_cmd[end]) == 1)
			end++;
		else
		{
			c_cmd[i] = wordle(s_cmd, end);
			i++;
		}
	}
	c_cmd[i] = 0;
	return (c_cmd)
}

char	**get_cmd(char *input, int st, int end)
{
	int		i;
	char	*s_cmd;
	char	**c_cmd;

	i = st;
	while (input[i])
	{
		if (input[i + 1] == '\'' || input[i + 1] == '\"')
		{
			s_cmd = ft_substr(input, st, i - st);
			st = i;
			break;
		}
		i++;
	}
	c_cmd = cmd_split(cmd);
	return (c_cmd);
}
