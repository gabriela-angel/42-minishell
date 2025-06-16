/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:50:25 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/20 16:50:25 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(const char *msg)
{
	if (!(*msg))
		msg = " ";
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", msg, strerror(errno));
	ft_gc_exit();
	return (!!errno);
}

int	exit_status(int set)
{
	static int	status;

	if (set != -1)
		status = set;
	return (status);
}

int	cleanup_and_exit(int status)
{
	char	**env;

	env = get_envp(NULL);
	delete_heredoc();
	if (env)
		ft_free_matrix(env);
	ft_gc_exit();
	rl_clear_history();
	exit_status(status);
	exit(exit_status(-1));
}

int	handle_err_exec(const char *msg, int res)
{
	if (res == -3)
	{
		ft_printf_fd(2, "minishell: -bash: %s: Is a directory\n", msg);
		return (126);
	}
	else if (res == -1)
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", msg);
		return (126);
	}
	else if (res == -2)
	{
		if (ft_strchr(msg, '/'))
			ft_printf_fd(2, "minishell: %s: No such file or directory\n", msg);
		else
			ft_printf_fd(2, "minishell: %s: command not found\n", msg);
		return (127);
	}
	return (res);
}
