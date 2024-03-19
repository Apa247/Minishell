/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:03:10 by daparici          #+#    #+#             */
/*   Updated: 2024/03/19 20:49:59 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_here_doc(t_command *cmd, char **env)
{
	int		pipe1[2];
	char	*line;
	//char	*aux;
	int		i;

	(void)env;
	i = 0;
	while (cmd->limiter[i])
	{
		pipe(pipe1);
		ft_putchar_fd('>', 2);
		line = get_next_line(0);
		while (ft_strlen(cmd->limiter[i]) != (ft_strlen(line) - 1)
			|| ft_strncmp(line, cmd->limiter[i], ft_strlen(cmd->limiter[i])))
		{
			//aux = check_str(line, env, 1);
			ft_putchar_fd('>', 2);
			ft_putstr_fd(line, pipe1[1]);
			free(line);
			line = get_next_line(0);
		}
		free(line);
		close(pipe1[1]);
		i++;
	}
	cmd->heredoc = pipe1[0];
}

char	*heredoc_loop(t_command *cmd, char **env)
{
	char	*input;
	char	*hdoc;
	int		heredoc_pipe[2];
	int		i;

	i = 0;
	pipe(heredoc_pipe);
	while (cmd->limiter[i])
	{
		ft_putnbr_fd(cmd->heredoc, 2);
		ft_putchar_fd('\n', 2);
		if (i > 0)
			free(hdoc);
		input = readline(">");
		hdoc = heredoc(input, cmd->limiter[i]);
		i++;
	}
	input = split_words(hdoc, env);
	ft_putstr_fd(input, heredoc_pipe[1]);
	cmd->heredoc = heredoc_pipe[0];
	return (input);
}

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