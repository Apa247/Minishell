/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2023/12/05 10:39:37 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	ft_executor(t_toolbox *tools)
{
	t_command	*cmd;

	cmd = tools->cmd;
	while (cmd)
	{
		if (ft_strcmp(cmd->cmd, "pwd") == 0)
			return (ft_pwd());
		else if(ft_strcmp(cmd->cmd, "echo") == 0)
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
	return(EXIT_SUCCESS);
}
