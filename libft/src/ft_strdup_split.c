/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:13:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/15 23:30:53 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_split(char **envp)
{
	int		i;
	int		count;
	char	**copy;

	if (!envp)
		return (NULL);
	count = 0;
	while (envp[count])
		count++;
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			ft_free_matrix(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
