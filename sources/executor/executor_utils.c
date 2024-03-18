/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:21:02 by davidaparic       #+#    #+#             */
/*   Updated: 2024/03/18 22:22:54 by davidaparic      ###   ########.fr       */
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

char	*find_paths(char **envp)
{
	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp)
		return (*envp + 5);
	else
		return (NULL);
}