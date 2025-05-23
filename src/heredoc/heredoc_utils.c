/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:26:24 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/16 21:26:24 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_heredoc(void)
{
	char	*file_name;
	int		*heredoc_counter;
	char	*str_counter;

	heredoc_counter = get_heredoc_counter();
	while ((*heredoc_counter) >= 0)
	{
		str_counter = ft_itoa((*heredoc_counter));
		file_name = ft_strjoin("/tmp/.heredoc", str_counter);
		unlink(file_name);
		free(str_counter);
		free(file_name);
		if (*heredoc_counter > 0)
			(*heredoc_counter)--;
		else
			break ;
	}
	return (SUCCESS);
}

int	*get_heredoc_counter(void)
{
	static int	counter;

	return (&counter);
}
