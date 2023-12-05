/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:11:02 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/14 16:04:56 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include	"../includes/minishell.h"

int	trig_swicth(int	qtrig)
{
	if (qtrig == 0)
		qtrig = 1;
	else
		qtrig = 0;
	return (qtrig);
}

int	token_redir(char a)
{
	if (a == '|' || a == '<' || a == '>')
		return (1);
	else
		return (0);
}

void	extract_cmd(t_cmds **cmd_list, input, st, end)
{
	int		qt;
	char	**cmd;
	char	*arg;
	t_token	tk;

	cmd = get_cmd(input, &st, end);
	arg = get_arg(input, &st, end);
	tk	= get_token(input, st,  end);
	cmd_addback(cmd_list, cmd_new(cmd, arg, tk);
}

void	parser(char *input)
{
	int		st;
	int		end;
	int		qtrig;
	t_cmds	*cmd_list

	st = 0;
	end = 0;
	qtrig = 0;
	while (input[end])
	{
		if (input[end] == '\"' || input[end] == '\"')
		{
			qtrig = trig_swicth(qtrig);
			st = end;
			end++;
			while (input[st] != input[end])
				end++;
			qtrig = trig_swicth(qtrig);
		}
		if (token_redir(input[end]) == 1 && qtrig == 0)
		{
			if (input[end] == input[end + 1])
				end++;
			extract_cmd(&cmd_list, input, st, end);
			st = end;
		}
		end++;
	}
}
