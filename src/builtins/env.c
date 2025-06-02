/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:47 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/02 12:10:52 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Imprime as variáveis de ambiente com '='.
 */
int	exec_env(char **args, char **env)
{
	int	i;

	if (args[1])
	{
		ft_printf_fd(2, "env: too many arguments\n");
		return (FAILURE);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf_fd(1, "%s\n", env[i]);
		i++;
	}
	return (SUCCESS);
}
