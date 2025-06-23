/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:46:39 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/23 19:46:24 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_bool	is_builtin(const char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "unset"))
		return (TRUE);
	return (FALSE);
}

int	exec_builtin(char **args, int last_status)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "cd"))
		return (exec_cd(args));
	if (!ft_strcmp(args[0], "echo"))
		return (exec_echo(args));
	if (!ft_strcmp(args[0], "env"))
		return (exec_env(args));
	if (!ft_strcmp(args[0], "exit"))
		return (exec_exit(args, last_status));
	if (!ft_strcmp(args[0], "export"))
		return (exec_export(args));
	if (!ft_strcmp(args[0], "pwd"))
		return (exec_pwd(args));
	if (!ft_strcmp(args[0], "unset"))
		return (exec_unset(args));
	return (handle_error("error executing builtin"));
}
