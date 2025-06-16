/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:00:10 by acesar-m          #+#    #+#             */
/*   Updated: 2025/06/15 22:53:08 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sorted_env(char **env, int count)
{
	int		i;
	char	*eq;
	char	*val;

	i = 0;
	while (i < count)
	{
		eq = ft_strchr(env[i], '=');
		if (eq && eq == env[i] + 1 && env[i][0] == '_')
		{
			i++;
			continue ;
		}
		if (eq)
		{
			*eq = '\0';
			val = eq + 1;
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", env[i], val);
			*eq = '=';
		}
		else
			ft_printf_fd(1, "declare -x %s\n", env[i]);
		i++;
	}
}

int	print_export_list(char **env)
{
	int		count;
	int		i;
	char	**copy;

	count = 0;
	while (env && env[count])
		count++;
	copy = ft_malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (1);
	ft_gc_add(copy);
	i = 0;
	while (i < count)
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = NULL;
	sort_env(copy, count);
	print_sorted_env(copy, count);
	ft_gc_free(copy);
	return (0);
}
