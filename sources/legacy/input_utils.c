/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:45:20 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/13 15:43:49 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	l_length(t_lexer *list)
{
	int		i;
	t_lexer	*aux;

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

void	l_free(t_lexer *lexer)
{
	if (lexer)
	{
		while (lexer->next)
		{
			if (lexer->word)
				free(lexer->word);
			lexer =  lexer->next;
			free(lexer->prev);
		}
		if (!lexer->next)
		{
			if (lexer->word)
				free(lexer->word);
			free(lexer);
		}
	}
}

void show_lexer(t_lexer	*lexer_list)
{
	t_lexer	*tmp;

	tmp = lexer_list;
	while (tmp)
	{
		if (tmp->word)
			printf("\n%s\n", tmp->word);
		else if (tmp->token > 0)
			printf("\n%d\n", tmp->token);
		tmp = tmp->next;
	}
	//l_free(lexer_list);
}
