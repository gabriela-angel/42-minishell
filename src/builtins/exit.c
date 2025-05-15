/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:30:19 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 18:25:46 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i = 0;

	if (!s)
		return (0);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
		if (!ft_isdigit(s[i++]))
			return (0);
	return (1);
}

int	exec_exit(char **args, int last_status)
{
	write(2, "exit\n", 5);
	if (!args[1])
		exit(last_status);
	if (!is_numeric(args[1]))
	{
		ft_printf_fd(2, "minishell: exit: numeric argument required\n", 44);
		exit(255);
	}
	if (args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	exit((unsigned char)ft_atoi(args[1]));
}