/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:19 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/22 17:49:50 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(char **args, int last_status)
{
	long long	nb;

	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (!args[1])
		cleanup_and_exit(last_status);
	if (!ft_strtoll_check(args[1], &nb))
	{
		ft_printf_fd(2, "exit: numeric argument required\n");
		cleanup_and_exit(2);
	}
	if (args[2])
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		cleanup_and_exit(1);
	}
	cleanup_and_exit((unsigned char)ft_atoi(args[1]));
	return (SUCCESS);
}
