/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:56:27 by daparici          #+#    #+#             */
/*   Updated: 2023/12/07 22:26:00 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "tokens.h"


//built-ins funcion
void	ft_executor(t_toolbox *tools);
//  echo
void	ft_echo(t_command *cmd);
void	print_arguments(char **arg, int i);
//  pwd
int		ft_pwd(void);
// 	env
void	ft_env(char **env);
int     check_equal_env(char *env);
//	export
void	ft_export(t_toolbox *tools);
char	**add_variable(char **sort_env, char *cmd_arg);
void	print_export(char **env);
void	export_error(char *cmd_arg);
int		lenght_to_equal(char *cmd_arg);
int		check_variable_exist(t_toolbox *tools, char *cmd_arg);
int		check_parametres(char *cmd_arg);
void	ft_unset(t_toolbox *tools);
char	**delete_variable(char **env, int i);

// unset
void	ft_unset(t_toolbox *tools);
char	**delete_variable(char **env, int i);
int     ft_check_equal(char *arg);

// cd
void	ft_cd(t_toolbox *tools);
void	render_env(t_toolbox *tools);
char	*get_env_dir(t_toolbox *tools, char *arg);
char    *get_absolute_dir(t_toolbox *tools);

#endif
