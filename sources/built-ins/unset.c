/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:50:15 by daparici          #+#    #+#             */
/*   Updated: 2023/11/25 21:41:55 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_toolbox *tools)
{
    int i;
    int j;
    char **tmp;

    i = 0;
    if (tools->cmd->args)
    {
        while (tools->cmd->args[i])
        {
            j = 0;
            while (tools->env[j])
            {
                if (!strncmp(tools->env[j], tools->cmd->args[i], ft_strlen(tools->cmd->args[i])))
                {
                    tmp = delete_variable(tools->env, j);
                    free(tools->env);
                    tools->env = tmp;
                }
                j++;
            }
            i++;
        }
    }
}

char    **delete_variable(char **env, int i)
{
    char    **env_copy;
    int     j;

    j = 0;
    while (env[j])
        j++;
    env_copy = ft_calloc(sizeof(char *), j);
    if (!env_copy)
        return(NULL);
    j = 0;
    while (env[j])
    {
        if (j == i)
            free(env[i]);
        else
            env_copy[j] = env[j];
        j++;
    }
    env_copy[j] = 0;
    return(env_copy);
}