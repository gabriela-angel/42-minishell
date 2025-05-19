/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:20:26 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/15 17:26:05 by acesar-m         ###   ########.fr       */
=======
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:20:26 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/18 22:48:56 by gangel-a         ###   ########.fr       */
>>>>>>> origin/gabi
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	minishell_exec(t_tree *tree, char ***env)
{
	if (!tree)
		return (1);
<<<<<<< HEAD
=======
	expand_tokens(tree);
>>>>>>> origin/gabi
	execute_tree(tree, env);
	return (0);
}
