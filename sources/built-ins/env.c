/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:39:05 by davidaparic       #+#    #+#             */
/*   Updated: 2023/12/07 23:39:38 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     check_equal_env(char *env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (env[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int    ft_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        if (check_equal_env(env[i]))
            ft_putendl_fd(env[i], STDOUT_FILENO);
        i++;
    }
    return (EXIT_SUCCESS);
}
