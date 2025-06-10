/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:19 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/10 16:45:24 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (SUCCESS);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (SUCCESS);
	return (1);
}

int	exec_exit(char **args, int last_status)
{
	if (!args[1])
		cleanup_and_exit(last_status);
	if (!is_numeric(args[1]))
	{
		ft_printf_fd(2, "exit: numeric argument required\n");
		ft_printf_fd(1, "exit\n");
		cleanup_and_exit(2);
	}
	if (args[2])
	{
		ft_printf_fd(2, "exit: too many arguments\n");
		ft_printf_fd(1, "exit\n");
		cleanup_and_exit(1);
	}
	ft_printf_fd(1, "exit\n");
	cleanup_and_exit((unsigned char)ft_atoi(args[1]));
	return (0);
}
