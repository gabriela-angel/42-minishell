/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:19 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/11 14:23:21 by acesar-m         ###   ########.fr       */
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
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (!args[1])
		cleanup_and_exit(last_status);
	if (!is_numeric(args[1]))
	{
		ft_printf_fd(2, "minishell: exit: numeric argument required\n");
		cleanup_and_exit(SYNTAX_ERROR);
	}
	if (args[2])
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		exit_status(1);
		return (FAILURE);
	}
	cleanup_and_exit((unsigned char)ft_atoi(args[1]));
	return (SUCCESS);
}
