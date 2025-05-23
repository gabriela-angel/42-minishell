/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:28:47 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 18:25:50 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * Imprime as variáveis de ambiente com '='.
 */
int	exec_env(char **args, char **env)
{
	int	i;

	if (args[1])
	{
		write(2, "env: too many arguments\n", 25);
		return (1);
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
