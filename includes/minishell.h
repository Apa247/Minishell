/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:07:55 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/02/08 18:08:30 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include "libft/libft.h"
#include "tokens.h"
#include "structs.h"
#include "lexer.h"
#include "parser.h"
#include "expander.h"
#include "builtins.h"


//test
t_command   *cmd_extract(t_lexer *list);
int check_syntax(t_lexer *tk_list);


//signal functions
void	signals_workout(void);

//loop functions
int		minishell_loop(t_toolbox *tools);
int		tools_load(t_toolbox *tools);
void	tools_reload(t_toolbox *tools);

//enviroment functions
char	**envp_dup(char **envp, t_toolbox *tools);
int		pwd_search(t_toolbox *tools);
char	**st_envp(char **envp);
char	**new_env(void);
char	*get_home(void);
void	sort_arr(char **arr);
//utility functions
//char		*expander(t_toolbox *tools, char *str);
void	free_arr(char **arr);
int		handle_quotes(char *input);
int		check_input(t_toolbox *tools);
int		check_quotes(char *str);
int		exit_code(void);
t_bool	switch_bool(t_bool bool);

//error functions
int		error_msg(char *msg);
int		error_token(t_token token);

//executor funcion
void	ft_executor(t_command *cmd);
int		ft_is_builtin(t_toolbox *tools);
//  echo
//void	ft_echo(t_sp_cmds *sp_cmds);
void	print_arguments(char **arg, int i);
//  pwd
int		ft_pwd(void);
#endif
