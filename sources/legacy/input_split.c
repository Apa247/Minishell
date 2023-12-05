/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:22 by jverdu-r          #+#    #+#             */
<<<<<<< HEAD:sources/input_split.c
/*   Updated: 2023/06/08 17:52:09 by daparici         ###   ########.fr       */
=======
/*   Updated: 2023/06/14 16:05:03 by jverdu-r         ###   ########.fr       */
>>>>>>> 2e6bdc2bff8ec99513594b2b36ef616cea68cdf7:sources/legacy/input_split.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_handler(t_lexer **lexer, char *input, int *st_tk, int end_tk)
{
	int		j;

	j = *st_tk + 1;
	while ((input[j] != input[*st_tk]) && input[j])
		j++;
	if (input[j] == 0)
		return (end_tk);
	j++;
	l_addback(lexer, l_new(ft_substr(input, *st_tk, j - *st_tk), 0));
	end_tk += j;
	end_tk = end_tk - *st_tk;
	*st_tk = end_tk;
	return (end_tk);
}

int	token_handler(t_lexer **lexer_list, char *input, int i)
{
	if (input[i] == '|')
		l_addback(lexer_list, l_new(NULL, 1));
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			l_addback(lexer_list, l_new(NULL, 3));
			return (2);
		}
		else
			l_addback(lexer_list, l_new(NULL, 2));
	}
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
		{
			l_addback(lexer_list, l_new(NULL, 5));
			return (2);
		}
		else
			l_addback(lexer_list, l_new(NULL, 4));
	}
	return (1);
}

t_lexer	*input_filter(char *ipt)
{
	int		ed_tk;
	int		st_tk;
	t_lexer	*lex;

	ed_tk = 0;
	st_tk = 0;
	lex = NULL;
	while (ipt[ed_tk])
	{
		if (ipt[ed_tk] == '\"' || ipt[ed_tk] == '\'')
			ed_tk = quote_handler(&lex, ipt, &st_tk, ed_tk);
		if (ipt[ed_tk] == '|' || ipt[ed_tk] == '<' || ipt[ed_tk] == '>')
		{
			if (st_tk != ed_tk && (ipt[ed_tk] != '|' || ipt[ed_tk] != '<' \
				|| ipt[ed_tk] != '>'))
				l_addback(&lex, l_new(ft_substr(ipt, st_tk, ed_tk - st_tk), 0));
			ed_tk += token_handler(&lex, ipt, ed_tk);
			st_tk = ed_tk;
		}
		else
			ed_tk++;
	}
	if (ed_tk != st_tk)
		l_addback(&lex, l_new(ft_substr(ipt, st_tk, ed_tk - st_tk), 0));
	return (lex);
}
