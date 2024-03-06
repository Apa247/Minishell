/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/06 19:16:01 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void	recursive_ex(int pre_pipe, t_command *cmd, int count, int limit)
{
	int	ac_pipe[2];

	pipe(ac_pipe);
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror("minishell:");
	else if (cmd->pid == 0)
	{
		if (cmd->here_doc && !cmd->args)
		{
			if (dup2(cmd->here_doc, 0))
				perror("minishell");
			close(cmd->here_doc);
		}
		else
		{
			if (cmd->in_fd > 2)
			{
				if (dup2(cmd->in_file, 0))
					perror("minishell");
				close ()
		}
	}
}

void	ft_executor(t_command *cmd)
{
	int			ac_pipe[2];
	t_command	*cmd_aux;
	int			count;
	int			limit;

	cmd_aux = cmd;
	count = 0;
	limit = ft_lstsize(cmd);
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
