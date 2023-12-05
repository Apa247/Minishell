/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:39:05 by davidaparic       #+#    #+#             */
/*   Updated: 2023/09/14 14:16:29 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
}
