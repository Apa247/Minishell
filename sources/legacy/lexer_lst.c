/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:52:32 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/17 14:33:41 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*parser_new(char **cmd, int token)
{
	t_cmds	*new;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->cmd = cmd;
//	new->builtins = builtin
	new->redir = token;
//	new->file_name	= lexer_file(&lexer);
//	new->redirections = lex_redirect(lexer);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmds *parser_last(t_cmds *lst)
{
	t_cmds	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	parser_delone(t_cmds **lst)
{
	if (lst && *lst)
	{
		if (parser_length(*lst) > 1)
		{
			lst[0] = lst[0]->next;
			free(lst[0]->prev);
			lst[0]->prev = NULL;
		}
		else
		{
			free(lst[0]);
			lst[0] = NULL;
		}
	}
}

void	parser_add(t_cmds **head, t_cmds *new)
{
	t_cmds	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		new->next = tmp;;
		tmp->prev = new;
		tmp = new;
		*head = tmp;
	}
}

void	parser_addback(t_cmds **head, t_cmds *new)
{
	t_cmds	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp)
		{
			if (!tmp->next)
			{
				tmp->next = new;
				new->prev = tmp;
				tmp = new;
			}
			tmp = tmp->next;
		}
	}
}
