/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:53:02 by daparici          #+#    #+#             */
/*   Updated: 2024/03/18 22:15:33 by davidaparic      ###   ########.fr       */
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

char	*find_path(char *cmd, char **path)
{
	char	*tmp;

	if (!access(cmd, X_OK))
		return (cmd);
	if (path)
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, "/");
			tmp = ft_strjoin(tmp, cmd);
			if (!access(tmp, X_OK))
				return (tmp);
			free(tmp);
			path++;
		}
		(perror(cmd), exit(1));
	}
	return (NULL);
}

char	**fill_args(t_command *cmd)
{
	char		**n_args;
	t_command	*aux;
	int			i;
	int			j;

	j = 0;
	aux = cmd;
	i = 0;
	if (aux->args)
		while (aux->args[i])
			i++;
	else
		i++;
	n_args = malloc(sizeof(char *) * (i + 2));
	n_args[0] = cmd->cmd;
	i = 1;
	if (aux->args)
		while (cmd->args[j])
			n_args[i++] = cmd->args[j++];
	n_args[i] = NULL;
	return (n_args);
}

void	manage_dups(t_command *cmd, int *pre_pipe, int *ac_pipe)
{
	if (cmd->prev)
	{
		if (dup2(pre_pipe[0], 0) < 0)
			(perror("minishell:"), exit(1));
		close(pre_pipe[0]);
	}
	if (cmd->next)
	{
		if (dup2(ac_pipe[1], 1) < 0)
			(perror("minishell:"), exit(1));
		close(ac_pipe[1]);
	}
	if (cmd->in_fd > 2)
	{
		if (dup2(cmd->in_fd, 0) < 0)
			(perror("minishell:"), exit(1));
		close(cmd->in_fd);
	}
	if (cmd->out_fd > 2)
	{
		if (dup2(cmd->out_fd, 1) < 0)
			(perror("minishell:"), exit(1));
		close(cmd->out_fd);
	}
}

char	*find_paths(char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp)
		return (*envp + 5);
	else
		return (NULL);
}

void manage_params_child(t_toolbox *tools, t_command *cmd)
{
	char	**cmd_arg;
	char	*cmd_rute;
	char	**path_rutes;
	char	*path_rute;

	cmd_arg = fill_args(cmd);
	if (!cmd_arg)
		(perror("minishell:"), exit(1));
	path_rute = find_paths(tools->env);
	if (!path_rute)
		(perror("minishell:"), exit(1));
	path_rutes = ft_split((char const *)path_rute, ':');
	if (!path_rutes)
		(perror("minishell:"), exit(1));
	cmd_rute = find_path(cmd->cmd, path_rutes);
	if (!cmd_rute)
		(perror("minishell:"), exit(1));
	if (execve(cmd_rute, cmd_arg, tools->env) < 0)
		(perror("minishell:"), exit(1));
}

void	m_hdoc_child(int *pre_p, int *ac_p, t_toolbox *tools, t_command *cmd)
{
	(close(pre_p[1]), close(ac_p[0]));
	if (!cmd->prev)
		close(pre_p[0]);
	if (!cmd->next)
		close(ac_p[1]);
	manage_dups(cmd, pre_p, ac_p);
	if (cmd->heredoc)
	{
		heredoc_loop(cmd, tools->env);
		if (cmd->heredoc && !cmd->args && cmd->in_fd <= 2)
		{
			if (dup2(cmd->heredoc, 0) < 0)
				(perror("minishell"), exit(1));
			close(cmd->heredoc);
		}
	}
}

void	recursive_ex(int *pre_pipe, t_command *cmd, t_toolbox *tools)
{
	int		ac_pipe[2];

	pipe(ac_pipe);
	cmd->pid = fork();
	if (cmd->pid < 0)
		(perror("minishell:"), exit(1));
	else if (cmd->pid == 0)
	{
		m_hdoc_child(pre_pipe, ac_pipe, tools, cmd);
		if (ft_is_builtin(cmd) == 0)
			(ft_is_builtin_2(tools, cmd), exit(0));
		else
			manage_params_child(tools, cmd);
	}
	else
	{
		if (cmd->next)
		{
			(close(pre_pipe[0]), close(pre_pipe[1]));
			recursive_ex(ac_pipe, cmd->next, tools);
			(close(ac_pipe[0]), close(ac_pipe[1]));
		}
	}
}

void	ft_executor(t_toolbox *tools)
{
	if (ft_lstsize_m(tools->cmd) > 1)
		ft_executor_loop(tools->cmd, tools);
	else
		ft_is_builtin_2(tools, tools->cmd);
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
