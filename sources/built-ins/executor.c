/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/07 15:59:45 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	manage_dups(t_command *cmd, int *pre_pipe, int *ac_pipe)
{
	if (cmd->prev)
	{
		if (dup2(pre_pipe[0], 0))
			(perror("minishell:"), exit(1))
		close(pre_pipe[0]);
	}
	if (cmd->next)
	{
		if (dup2(ac_pipe[1], 1))
			(perror("minishell:"), exit(1))
		close(ac_pipe[1]);
	}
	if (cmd->in_fd > 2)
	{
		if (dup2(cmd->in_fd, 0))
			(perror("minishell:"), exit(1));
		close(cmd->in_fd);
	}
	if (cmd->out_fd > 2)
	{
		if (dup2(cmd->out_fd, 1))
			(perror("minishell:"), exit(1));
		close(cmd->out_fd);
	}
}

void	recursive_ex(int *pre_pipe, t_command *cmd)
{
	int	ac_pipe[2];

	pipe(ac_pipe);
	cmd->pid = fork();
	if (cmd->pid < 0)
		(perror("minishell:"), exit(1));
	else if (cmd->pid == 0)
	{
		if (cmd->here_doc && !cmd->args && cmd->in_fd <= 2)
		{
			if (dup2(cmd->here_doc, 0))
				(perror("minishell"), exit(1));
			close(cmd->here_doc[0]);
		}
		else
		{
			manage_dups(cmd, pre_pipe, ac_pipe);
		}
	}
	else
	{
		if (cmd->next)
		{
			close(pre_pipe[0]);
			close(pre_pipe[1]);
			recursive_ex()
		}
	}
}

void	ft_executor(t_command *cmd)
{
	int			ac_pipe[2];
	t_command	*cmd_aux;

	cmd_aux = cmd;
	recursive_ex(ac_pipe, cmd_aux, count, limit);
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
