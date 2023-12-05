/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:22:42 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/11/03 16:35:03 by jverdu-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_in_fd(t_redir *redir)
{
	t_redir	*in_files;

	in_files = redir;
	while (in_files)
	{
		if (access(in_files->file, R_OK) == -1)
		{
			if (errno == EACCES)
				error_msg("Access denied\n");
			else if (errno == ENOENT)
				error_msg("File does not exist\n");
			else
				error_msg("Access error\n");
		}
		in_files = in_files->next;
	}
}

void	check_out_fd(t_command *cmd)
{
	t_redir	*out_files;

	out_files = cmd->out_files;
	while (out_files)
	{
		cmd->out_fd = open(out_files->file, O_CREAT | O_WRONLY | O_TRUNC);
		close(cmd->out_fd);
		out_files = out_files->next;
	}
}

void	get_fds(t_command *raw_cmd)
{
	t_command	*cmd;

	cmd = raw_cmd;
	while (cmd)
	{
		if (cmd->in_files)
			check_in_fd(cmd->in_files);
		if (cmd->out_files)
			check_out_fd(cmd);
		cmd = cmd->next;
	}
}
