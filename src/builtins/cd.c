/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:52 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/10 15:43:33 by acesar-m         ###   ########.fr       */
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

	if (!args[1])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf_fd(2, "cd: HOME not set\n");
			return (1);
		}
		path = home;
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		ft_printf_fd(2, "cd: %s: No such file or directory\n", path);
		return (1);
	}
	update_pwd();
	return (0);
}
