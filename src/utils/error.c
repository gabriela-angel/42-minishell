/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:00 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 13:27:45 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *token)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%s'\n", token);
	return (set_exit_status(SYNTAX_ERROR));
}

int throw_error(char *cmd_path)
{
	if (*cmd_path == '\0')
		cmd_path = " ";
	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
	{
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied\n", cmd_path);
		return (126);
	}
	else if ((*cmd_path == '.' || ft_strchr(cmd_path, '/')) && !access(cmd_path, F_OK))
	{
		ft_printf_fd(STDERR_FILENO, "%s: Is a directory\n", cmd_path);
		return (126);
	}
	else if (errno == 2 || !getenv("PATH"))
	{
		ft_printf_fd(STDERR_FILENO, "%s: No such file or directory\n", cmd_path);
		return (127);
	}
	else
		return (!!write(STDERR_FILENO, "minishell: unexpected error\n", 28));
}

int handle_error(char *message)
{
	if (*message == '\0')
		message = " ";
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", message, strerror(errno));
	ft_gc_exit();
	return (!!errno);
}

int signal_error(void)
{
	ft_printf_fd(STDERR_FILENO, "minishell: failed to install signal handler\n");
	return (FAILURE);
}
