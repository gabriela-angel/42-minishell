/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:49:54 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/19 21:37:59 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		ft_gc_free(split[i]);
		i++;
	}
	ft_gc_free(split);
}

void	ft_sort_strs(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	var_exists(char *arg, char **env, int *index)
{
	int		i;
	char	*name;
	size_t	len;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!name)
		return (0);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			*index = i;
			ft_gc_free(name);
			return (1);
		}
		i++;
	}
	ft_gc_free(name);
	return (0);
}

static char	**create_new_env(char *arg, char **env, int size)
{
	char	**new;
	int		i;

	new = ft_malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = env[i];
		i++;
	}
	new[size] = ft_strdup(arg);
	new[size + 1] = NULL;
	return (new);
}

int	ft_setenv(char *arg, char ***env)
{
	int		index;
	int		size;
	char	**new;

	if (var_exists(arg, *env, &index))
	{
		ft_gc_free((*env)[index]);
		(*env)[index] = ft_strdup(arg);
		return (!(*env)[index]);
	}
	size = 0;
	while ((*env)[size])
		size++;
	new = create_new_env(arg, *env, size);
	if (!new)
		return (1);
	ft_gc_free(*env);
	*env = new;
	return (!new[size]);
}

int handle_error(const char *msg)
{
	ft_printf_fd(2, "minishell: %s\n", msg);
	return (1);
}

int	exit_status(int set)
{
	static int	status = 0;

	if (set != -1)
		status = set;
	return status;
}
