/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/18 22:27:10 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_executor(t_toolbox *tools)
{
	if (ft_lstsize_m(tools->cmd) > 1)
		ft_executor_loop(tools->cmd, tools);
	else
	{
		if (ft_is_builtin(tools->cmd) == 0)
			ft_is_builtin_2(tools, tools->cmd);
		else
			
	}
}

void	ft_executor_loop(t_command *cmd, t_toolbox *tools)
{
	int			ac_pipe[2];
	t_command	*cmd_aux;
	int			i;
	int			status;

	i = 0;
	cmd_aux = cmd;
	pipe(ac_pipe);
	recursive_ex(ac_pipe, cmd_aux, tools);
	close(ac_pipe[0]);
	close(ac_pipe[1]);
	while (cmd_aux)
	{
		if (waitpid(cmd_aux->pid, &status, 0) == -1)
			(perror("minishell:"), exit(1));
		if (cmd_aux->next)
			cmd_aux = cmd_aux->next;
		else
			break ;
	}
}

int	ft_is_builtin(t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (0);
	else
		return (1);
}

void	ft_is_builtin_2(t_toolbox *tools, t_command *cmd)
{
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		ft_env(tools->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
		ft_export(tools);
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
		ft_unset(tools);
	else if (ft_strcmp(cmd->cmd, "cd") == 0)
		ft_cd(tools);
}
