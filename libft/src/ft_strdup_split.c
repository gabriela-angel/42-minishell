/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:13:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/19 21:37:41 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

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
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
