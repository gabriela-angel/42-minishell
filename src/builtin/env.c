/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:06:22 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:07:16 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_tree *command_tree)
{
	int		i;
	char	**env;

	if (!command_tree || !command_tree->command)
		return (handle_error("invalid command tree"));
	if (token_lst_get_size(command_tree->command) > 1)
		return (!!write(STDERR_FILENO, "env: too many arguments\n", 24));
	env = *get_my_env();
	i = -1;
	while (env[++i])
	{
		if (env[i][0] && ft_strchr(env[i], '='))
			ft_printf_fd(STDOUT_FILENO, "%s\n", env[i]);
	}
	return (EXIT_SUCCESS);
}
