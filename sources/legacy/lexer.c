/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:43:37 by jverdu-r          #+#    #+#             */
<<<<<<< HEAD:sources/lexer.c
/*   Updated: 2023/06/08 16:50:07 by daparici         ###   ########.fr       */
=======
/*   Updated: 2023/06/13 15:37:19 by jverdu-r         ###   ########.fr       */
>>>>>>> 2e6bdc2bff8ec99513594b2b36ef616cea68cdf7:sources/legacy/lexer.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_parser(char	*input)
{
	if (ft_strcmp(input, "|") == 0)
		return (1);
	else if (ft_strcmp(input, "<") == 0)
		return (2);
	else if (ft_strcmp(input, "<<") == 0)
		return (3);
	else if (ft_strcmp(input, ">") == 0)
		return (4);
	else if (ft_strcmp(input, ">>") == 0)
		return (5);
	else
		return (0);
}

void	show_split(char **split)
{
	int	x;

	x = 0;
	while (split[x])
	{
<<<<<<< HEAD:sources/lexer.c
		tk = token_parser(input[i]);
		if (tk != 0)
			lexer_addback(&lexer, lexer_new(NULL, tk));
		else
			lexer_addback(&lexer, lexer_new(input[i], 0));
		tk = 0;
		i++;
=======
		printf("%s ", split[x]);
		x++;
>>>>>>> 2e6bdc2bff8ec99513594b2b36ef616cea68cdf7:sources/legacy/lexer.c
	}
	printf("\n");
}
void	get_cmds(t_lexer *lex)
{
	t_cmds	*cmds;

	cmds = NULL;
	show_lexer(lex);
	while (lex->next)
	{
		if (lex->word)
		{
			parser_addback(&cmds, parser_new(ft_split(lex->word, ' '), 0));
		}
		else if (lex->token)
			parser_addback(&cmds, parser_new(NULL, lex->token));
		lex = lex->next;
	}
	if (lex->word)
		parser_addback(&cmds, parser_new(ft_split(lex->word, ' '), 0));
	else if (lex->token)
		parser_addback(&cmds, parser_new(NULL, lex->token));
	show_parser(cmds);
	l_free(lex);
	//system("leaks -q minishell");
}
