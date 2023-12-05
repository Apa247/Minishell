/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:45:56 by jverdu-r          #+#    #+#             */
<<<<<<< HEAD:sources/lexer_lst.c
/*   Updated: 2023/06/08 17:50:53 by daparici         ###   ########.fr       */
=======
/*   Updated: 2023/06/09 12:45:13 by jverdu-r         ###   ########.fr       */
>>>>>>> 2e6bdc2bff8ec99513594b2b36ef616cea68cdf7:sources/legacy/input_lst.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*l_new(char *word, t_token token)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->word = word;
	new->token = token;
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*l_last(t_lexer *lst)
{
	t_lexer	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	l_delone(t_lexer **lst)
{
	if (lst && *lst)
	{
		if (l_length(*lst) > 1)
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

void	l_add(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		new->next = tmp;
		tmp->index = new->index + 1;
		tmp->prev = new;
		tmp = new;
		*head = tmp;
	}
}

void	l_addback(t_lexer **head, t_lexer *new)
{
	t_lexer	*tmp;

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
				new->index = tmp->index + 1;
				tmp = new;
			}
			tmp = tmp->next;
		}
	}
}
