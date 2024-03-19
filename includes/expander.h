/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daparici <daparici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:59:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2024/03/19 20:31:47 by daparici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
#define EXPANDER_H

#include "libft/libft.h"
#include "structs.h"
#include "minishell.h"

void    expander(t_toolbox *tools);
char    *exp_word(char *str, char **env);
char	*arr_join(char **arr);
int     word_count(char *str);
char    *split_words(char *str, char **env);
char	*split_trim(char *str);
char	*get_res(char **words, char **env);
char	*get_trim(char **words);
char	**get_words(char **words);
char	**exp_words(char **words, char **env);
char	*expnd(char *str, char **env);
char	*check_str(char *str, char **env, int i);
#endif