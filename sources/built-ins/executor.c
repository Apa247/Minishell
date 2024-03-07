/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/07 19:39:33 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize_m(t_command *list)
{
	int			len;
	t_command	*temp;

	len = 0;
	temp = list;
	if (!list)
		return (0);
	while (temp->next != NULL)
	{
		temp = temp->next;
		len++;
	}
	if (temp->next == NULL)
		len++;
	return (len);
}

char	*pathfinder(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
	return (0);
}

char	**fill_args(t_command *cmd)
{
	char		**n_args;
	t_command	*aux;
	int			i;

	aux = cmd;
	i = 0;
	while (aux->args[i])
		i++;
	n_args = malloc(sizeof(char *) * (i + 2));
	n_args[0] = cmd->cmd;
	i = 1;
	while (cmd->args[i - 1])
	{
		n_args[i] = cmd->args[i - 1];
		i++;
	}
	n_args[i] = 0;
	return (n_args);
}

void	manage_dups(t_command *cmd, int *pre_pipe, int *ac_pipe)
{
	if (cmd->prev)
	{
		if (dup2(pre_pipe[0], 0))
			(perror("minishell:"), exit(1));
		close(pre_pipe[0]);
	}
	if (cmd->next)
	{
		if (dup2(ac_pipe[1], 1))
			(perror("minishell:"), exit(1));
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

void	recursive_ex(int *pre_pipe, t_command *cmd, t_toolbox *tools)
{
	int		ac_pipe[2];
	char	**cmd_arg;
	char	*cmd_path;

	pipe(ac_pipe);
	cmd->pid = fork();
	if (cmd->pid < 0)
		(perror("minishell:"), exit(1));
	else if (cmd->pid == 0)
	{
		(close(pre_pipe[1]), close(ac_pipe[0]));
		if (!cmd->prev)
			close(pre_pipe[0]);
		if (!cmd->next)
			close(ac_pipe[1]);
		manage_dups(cmd, pre_pipe, ac_pipe);
		if (cmd->heredoc)
		{
			heredoc_loop(cmd, tools->env);
			if (cmd->heredoc && !cmd->args && cmd->in_fd <= 2)
			{
				if (dup2(cmd->heredoc, 0))
					(perror("minishell"), exit(1));
				close(cmd->heredoc);
			}
		}
		// if (ft_is_builtin(tools))
		// 	exit(1);
		cmd_arg = fill_args(cmd);
		
		//cmd_path = pathfinder(cmd->cmd, tools->env);
		write(2, "hola\n", 5);
		if (!cmd_path)
			(perror("minishell:"), exit(1));
		if (execve(cmd_path, cmd_arg, tools->env) < 0)
			(perror("minishell:"), exit(1));
	}
	else
	{
		if (cmd->next)
		{
			close(pre_pipe[0]);
			close(pre_pipe[1]);
			recursive_ex(ac_pipe, cmd->next, tools);
		}
	}
}

void	ft_executor(t_toolbox *tools)
{
	if (ft_lstsize_m(tools->cmd) > 1)
		ft_executor_loop(tools->cmd, tools);
	else
		ft_is_builtin(tools);
}

void	ft_executor_loop(t_command *cmd, t_toolbox *tools)
{
	int			ac_pipe[2];
	t_command	*cmd_aux;

	cmd_aux = cmd;
	pipe(ac_pipe);
	recursive_ex(ac_pipe, cmd_aux, tools);
}

int	ft_is_builtin(t_toolbox *tools)
{
	if (ft_strcmp(tools->cmd->cmd, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(tools->cmd->cmd, "echo") == 0)
		return (ft_echo(tools->cmd));
	else if (ft_strcmp(tools->cmd->cmd, "env") == 0)
		return (ft_env(tools->env));
	else if (ft_strcmp(tools->cmd->cmd, "export") == 0)
		return (ft_export(tools));
	else if (ft_strcmp(tools->cmd->cmd, "unset") == 0)
		return (ft_unset(tools));
	else if (ft_strcmp(tools->cmd->cmd, "cd") == 0)
		return (ft_cd(tools));
	else
		return (EXIT_FAILURE);
}
