/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:52 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/11 12:13:12 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	free(cwd);
}

int	exec_cd(char **args)
{
	const char	*path;
	char		*home;

	if (args[1] && args[2])
	{
		ft_printf_fd(2, "cd: too many arguments\n");
		return (FAILURE);
	}
	if (!args[1] && !(home = getenv("HOME")))
	{
		ft_printf_fd(2, "cd: HOME not set\n");
		return (FAILURE);
	}
	path = args[1] ? args[1] : home;
	if (chdir(path))
	{
		ft_printf_fd(2, "cd: %s: No such file or directory\n", path);
		return (FAILURE);
	}
	update_pwd();
	return (SUCCESS);
}
