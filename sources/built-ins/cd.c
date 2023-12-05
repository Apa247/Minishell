/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 21:39:42 by davidaparic       #+#    #+#             */
/*   Updated: 2023/12/05 13:21:40 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_dir(t_toolbox *tools, char *arg)
{
    int i;

    i = 0;
    while (tools->env[i])
    {
        if (ft_strncmp(tools->env[i], arg, ft_strlen(arg)) == 0)
            return(&tools->env[i][5]);
        i++;
    }
    return(0);
}

char    *get_absolute_dir(t_toolbox *tools)
{
    char    *tmp;
    char    *absolute_dir;

    tmp = ft_strjoin(getcwd(NULL, 0), "/");
    absolute_dir = ft_strjoin(tmp, tools->cmd->args[0]);
    free(tmp);
    return(absolute_dir);
}

void	render_env(t_toolbox *tools)
{
    char    *oldpwd;
    char    *pwd;

    if (tools->old_pwd)
        free(tools->old_pwd);
    tools->old_pwd = tools->pwd;
    free(tools->pwd);
    tools->pwd = getcwd(NULL, 0);
    pwd = ft_strjoin("PWD=", tools->pwd);
    oldpwd = ft_strjoin("OLDPWD=", tools->old_pwd);
    check_variable_exist(tools, pwd);
    check_variable_exist(tools, oldpwd);
    free(pwd);
    free(oldpwd);
}

void	ft_cd(t_toolbox *tools)
{
    char    *dir;

    if (!tools->cmd->args)
    {
        dir = get_env_dir(tools, "HOME=");
        if (!dir || chdir(dir) == -1)
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        else
            render_env(tools);
        //printf("%s\n", dir);
    }
    else
    {
        if (chdir(tools->cmd->args[0]) == -1)
        {
            ft_putstr_fd("minishell: cd: ", 2);
            ft_putstr_fd(tools->cmd->args[0], 2);
            ft_putstr_fd(" not set\n", 2);
        }
        else
            render_env(tools);
    }
}