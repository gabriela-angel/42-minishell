/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:12:54 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:12:22 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_argument(t_tk_list *tokens, long *status)
{
	*status = (long)ft_atoi(tokens->next->token.value); // Converte o retorno de ft_atoi para long
	if (validate_argument(tokens->next->token.value)
		|| *(tokens->next->token.value) == '\0')
	{
		ft_printf_fd(STDERR_FILENO, "exit: %s: numeric argument required\n",
			tokens->next->token.value);
		ft_gc_exit();
		exit(SYNTAX_ERROR);
	}
	if (tokens->next->next)
	{
		ft_printf_fd(STDERR_FILENO, "exit: too many arguments\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	execute_exit(t_tree *command_tree)
{
	long		status;
	t_tk_list	*tokens;

	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	tokens = command_tree->command;
	status = 0;
	if (tokens->next && handle_exit_argument(tokens, &status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_gc_exit();
	exit(status ? status % 256 : *get_exit_status());
	return (EXIT_SUCCESS);
}

int	validate_argument(char *arg)
{
	int		i;
	char	sign;

	i = 0;
	sign = '+';
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = arg[i];
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAILURE);
		i++;
	}
	if (check_limits(arg, sign) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_limits(char *arg, char sign)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	if (ft_strlen(arg) > 19)
		return (FAILURE);
	if (ft_strlen(arg) < 19)
		return (SUCCESS);
	if ((ft_strcmp(arg, "9223372036854775807") > 0 && sign == '+')
		|| (ft_strcmp(arg, "9223372036854775808") > 0 && sign == '-'))
		return (FAILURE);
	return (SUCCESS);
}
