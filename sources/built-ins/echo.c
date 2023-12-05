/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:17:51 by daparici          #+#    #+#             */
/*   Updated: 2023/11/23 19:25:16 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_arguments(char **arg, int i)
{
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}

void	ft_echo(t_command *cmd)
{
	int		flag;
	size_t	i;
	size_t	j;

	flag = 0;
	i = 0;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 2))
	{
		j = 1;
		while (cmd->args[i][j] && cmd->args[i][j] == 'n')
			j++;
		if (j != ft_strlen(cmd->args[i]) && cmd->args[i][j] != 'n')
			break ;
		flag = 1;
		i++;
	}
	if (cmd->args[i])
		print_arguments(cmd->args, i);
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
