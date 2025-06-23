/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:31:26 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/23 19:46:54 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_bool	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exec_echo(char **args)
{
	int		i;
	t_bool	newline;

	i = 1;
	newline = TRUE;
	if (args[1] && is_n_flag(args[1]))
	{
		newline = FALSE;
		i++;
	}
	while (args[i])
	{
		ft_printf_fd(1, "%s", args[i]);
		if (args[i + 1])
			ft_printf_fd(1, " ");
		i++;
	}
	if (newline)
		ft_printf_fd(1, "\n");
	return (0);
}
