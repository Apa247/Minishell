/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/02/08 18:08:51 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_command *cmd)
{
	int			pip[2];
	int			pid;
	t_command	cmd_aux;

	aux = cmd;
	if (heredoc == ok)
	{
		pip[0] = ft_heredoc();
	}
	while (cmd)
	{
		
	}
}

int	ft_is_builtin(t_toolbox *tools)
{
	t_command	*cmd;

	cmd = tools->cmd;
	while (cmd)
	{
		if (ft_strcmp(cmd->cmd, "pwd") == 0)
			return (ft_pwd());
		else if (ft_strcmp(cmd->cmd, "echo") == 0)
			return (ft_echo(cmd));
		else if (ft_strcmp(cmd->cmd, "env") == 0)
			return (ft_env(tools->env));
		else if (ft_strcmp(cmd->cmd, "export") == 0)
			return (ft_export(tools));
		else if (ft_strcmp(cmd->cmd, "unset") == 0)
			return (ft_unset(tools));
		else if (ft_strcmp(cmd->cmd, "cd") == 0)
			return (ft_cd(tools));
		else
			return (EXIT_FAILURE);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
