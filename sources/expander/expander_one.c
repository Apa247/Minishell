/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:06:57 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/16 19:09:38 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_str(char *str, char **env, int i)
{
	char	*aux;

	if (i == 0)
	{
		aux = split_words(str, env);
		free(str);
	}
	else
	{
		aux = split_trim(str);
		free(str);
	}
	return (aux);
}

void	check_redir(t_redir *red, char **env)
{
	t_redir	*aux;
	char	*str;

	aux = red;
	while (aux)
	{
		if (ft_strlen(aux->file) > 2)
			str = check_str(aux->file, env, 0);
		else
			str = aux->file;
		aux->file = str;
		aux = aux->next;
	}
}

char	**check_args(char **args, char **env, int t)
{
	int		i;
	char	**aux;

	i = 0;
	while (args[i])
		i++;
	aux = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) > 2)
			aux[i] = check_str(args[i], env, t);
		else
			aux[i] = args[i];
		i++;
	}
	aux[i] = 0;
	free(args);
	return (aux);
}

void	expander(t_toolbox *tools)
{
	t_command	*cmd;
	int			i;

	cmd = tools->cmd;
	i = 0;
	while (cmd)
	{
		if (ft_strlen(cmd->cmd) > 2)
			cmd->cmd = check_str(cmd->cmd, tools->env, 0);
		if (cmd->append && ft_strlen(cmd->append) > 2)
			cmd->append = check_str(cmd->append, tools->env, 0);
		if (cmd->args)
			cmd->args = check_args(cmd->args, tools->env, 0);
		if (cmd->in_files)
			check_redir(cmd->in_files, tools->env);
		if (cmd->out_files)
			check_redir(cmd->out_files, tools->env);
		if (cmd->limiter)
			cmd->limiter = check_args(cmd->limiter, tools->env, 1);
		cmd = cmd->next;
	}
}
