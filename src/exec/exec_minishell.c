/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:20:26 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/15 13:54:07 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	minishell_exec(t_tree *tree, char ***env)
{
	if (!tree)
		return (1);
	ft_printf_fd(1, "Executing command tree...\n"); // Depuração
	execute_tree(tree, env);
	return (0);
}
