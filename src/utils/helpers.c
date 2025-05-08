/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:46 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/06 12:56:03 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	***get_my_env(void)
{
	static char	**env;

	return (&env);
}

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	set_exit_status(int status)
{
	int	*exit_status;

	exit_status = get_exit_status();
	*exit_status = status;
	return (*exit_status);
}

void	close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}
