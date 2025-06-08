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
	char **env;

	env = get_envp(NULL);
	delete_heredoc();
	ft_free_matrix(env);
	ft_gc_exit();
	rl_clear_history();
	exit_status(status);
	exit(exit_status(-1));
}
