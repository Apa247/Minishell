/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:46:33 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/17 14:24:09 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_length(t_cmds *list)
{
	int		i;
	t_cmds	*aux;

	if (!list)
		return (0);
	aux = list;
	i = 0;
	while (aux)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

void	free_cmds(char	**cmds)
{
	int	x;

	x = 0;
	while (cmds[x])
	{
		free(cmds[x]);
		x++;
	}
	free(cmds);
}

void	p_free(t_cmds *cmds)
{
	int x;

	x = 0;
	if (cmds)
	{
		while (cmds->next)
		{
			if (cmds->cmd)
				free_cmds(cmds->cmd);
			cmds =  cmds->next;
			free(cmds->prev);
		}
		if (!cmds->next)
		{
			if (cmds->cmd)
				free_cmds(cmds->cmd);
		}
		free(cmds);;
	}
}


void show_parser(t_cmds	*cmds)
{
	t_cmds	*tmp;
	int		x;

	tmp = cmds;
	printf("\n");
	while (tmp)
	{
		if (tmp->cmd)
		{
			x = 0;
			while (tmp->cmd[x])
			{
				printf("%s ", tmp->cmd[x]);
				x++;
			}
		}
		else if (tmp->redir > 0)
			printf("%d ", tmp->redir);
		tmp = tmp->next;
	}
	printf("\n");
	p_free(cmds);
}
