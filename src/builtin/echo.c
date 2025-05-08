/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:05:25 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:06:57 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_flag(char *str)
{
	if (*str == '-' && *(str + 1) == 'n')
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

void	print_args(char **args, int has_n_flag)
{
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (!has_n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	execute_echo(t_tree *command_tree)
{
	char	**args;
	int		has_n_flag;

	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	has_n_flag = 0;
	args = get_cmd_and_args(command_tree->command);
if (!args)
		return (handle_error("failed to parse arguments"));
	args++;
	while (args && *args && check_n_flag(*args))
	{
		has_n_flag = 1;
		args++;
	}
	print_args(args, has_n_flag);
	return (EXIT_SUCCESS);
}
