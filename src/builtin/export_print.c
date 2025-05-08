/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:13:27 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:22:46 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_and_print(const char *env_var)
{
	char	*name;
	char	*equal;
	char	*value;
	char	*copy;

	copy = ft_strdup(env_var);
	if (!copy || !ft_gc_add(copy))
	{
		free(copy);
		return;
	}
	equal = ft_strchr(copy, '=');
	if (!equal)
		printf("declare -x %s\n", copy);
	else
	{
		*equal = '\0';
		name = copy;
		value = equal + 1;
		printf("declare -x %s=\"%s\"\n", name, value);
	}
	free(copy);
}

int	print_smallest_unprinted(char **env, size_t env_size, char *printed)
{
	int	small_pos;

	small_pos = -1;
	while (env_size-- > 0)
	{
		if (printed[env_size])
			continue ;
		if (small_pos == -1 || ft_strcmp(env[small_pos], env[env_size]) > 0)
			small_pos = env_size;
	}
	if (small_pos != -1)
	{
		format_and_print(env[small_pos]);
		printed[small_pos]++;
		return (1);
	}
	return (0);
}

void	print_environ_sorted(void)
{
	char	*printed;
	size_t	size;
	char	**env;

	env = *get_my_env();
	if (!env)
		return ;
	size = 0;
	while (env[size])
		size++;
	printed = ft_calloc(size + 1, sizeof(char));
	if (!printed)
		return ;
	while (print_smallest_unprinted(env, size, printed))
		;
	free(printed);
}
