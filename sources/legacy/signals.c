/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:52:14 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/06/14 19:56:26 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_int(int code)
{
	(void)code;
	printf("minishell>");
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}
void	signals_workout(void)
{
	signal(SIGINT, signal_int);
	signal(SIGQUIT, SIG_IGN);
}
