/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:05:37 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 13:34:52 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cd(t_tree *command_tree)
{
	char **args;

	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	if (token_lst_get_size(command_tree->command) > 2)
		return (!!write(STDERR_FILENO, "cd: too many arguments\n", 23));
	args = get_cmd_and_args(command_tree->command);
	if (!args)
		return (handle_error("failed to parse arguments"));
	if (!args[1] || !ft_strcmp(args[1], "~"))
		return (change_to_home());
	return (change_dir(args[1]));
}

int change_to_home(void)
{
	char *home;
	char *old_dir;
	char *new_dir;

	old_dir = get_cwd();
	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) == -1)
			return (handle_error(home));
		set_env(ft_strjoin("OLDPWD=", old_dir), "OLDPWD", old_dir);
		new_dir = get_cwd();
		set_env(ft_strjoin("PWD=", new_dir), "PWD", new_dir);
		return (SUCCESS);
	}
	else
		return (!!write(STDERR_FILENO, "cd: HOME not set\n", 17));
}

int change_dir(char *path)
{
	char *old_dir;
	char *new_dir;

	old_dir = get_cwd();
	if (check_access(path) == 1)
		return (FAILURE);
	if (chdir(path) == -1)
		return (handle_error(path));
	set_env(ft_strjoin("OLDPWD=", old_dir), "OLDPWD", old_dir);
	new_dir = get_cwd();
	set_env(ft_strjoin("PWD=", new_dir), "PWD", new_dir);
	return (SUCCESS);
}

int check_access(char *path)
{
	if (access(path, F_OK))
		return (!!ft_printf_fd(STDERR_FILENO, "cd: %s: no such file or directory\n", path));
	else if (access(path, R_OK))
		return (!!ft_printf_fd(STDERR_FILENO, "cd: %s: permission denied\n", path));
	return (SUCCESS);
}

char *get_cwd(void)
{
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        handle_error("cd");
    if (!ft_gc_add(cwd))
    {
        free(cwd);
        handle_error("failed to register memory");
    }
    return (cwd);
}
