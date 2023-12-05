/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdu-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:59:56 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/10/24 17:59:58 by jverdu-r         ###   ########.fr       */
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
#endif