/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:03:10 by daparici          #+#    #+#             */
/*   Updated: 2024/03/07 16:04:47 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc(char *input, char *lim)
{
	char	*aux;
	char	*pipe;

	if (ft_strncmp(input, lim, ft_strlen(lim)))
		return (NULL);
	while (42)
	{
		aux = readline(">");
		if (ft_strncmp(aux, lim, ft_strlen(lim)))
		{
			free(aux);
			break ;
		}
		pipe = ft_strjoin(input, "\n");
		input = ft_strjoin(pipe, aux);
		free(pipe);
		free(aux);
	}
	return (input);
}

char	*heredoc_loop(t_command *cmd, char **env)
{
	char	*input;
	char	*hdoc;
	int		i;

	i = 0;
	while (cmd->limiter[i])
	{
		if (i > 0)
			free(hdoc);
		input = readline(">");
		hdoc = heredoc(input, cmd->limiter[i]);
		i++;
	}
	input = split_words(hdoc, env);
	return (input);
}
