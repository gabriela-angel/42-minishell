/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:16:39 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:02:59 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: getcwd failed");
		ft_printf_fd(STDERR_FILENO, "errno: %d\n", errno);
		return (handle_error("pwd"));
	}
	if (!ft_gc_add(path))
	{
		ft_printf_fd(STDERR_FILENO, "pwd: ft_gc_add failed\n");
		ft_gc_free(path);
		return (handle_error("pwd: failed to register memory"));
	}
	printf("%s\n", path);
	return (EXIT_SUCCESS);
}