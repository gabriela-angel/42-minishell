/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:41:32 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/23 19:47:11 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	exec_pwd(char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
