/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:50:29 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/24 11:51:46 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*verify_cmd(char *cmd, int *res)
{
	struct stat	info;

	*res = 0;
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) != 0 || stat(cmd, &info) != 0)
		{
			if (errno == EACCES)
				*res = -1;
			else if (errno == ENOENT)
				*res = -2;
			else
				*res = -3;
			return (NULL);
		}
		if (S_ISDIR(info.st_mode))
		{
			*res = -3;
			return (NULL);
		}
		return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin_free(tmp, cmd);
	ft_gc_add(res);
	return (res);
}
