/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:08:01 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 14:29:48 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (handle_error("heredoc: failed to create pipe"));

	while (1)
	{
		line = readline("> ");
		if (!line) // Verifica se readline falhou ou EOF foi encontrado
		{
			close(pipe_fd[1]); // Fecha o lado de escrita do pipe
			close(pipe_fd[0]); // Fecha o lado de leitura do pipe
			return (handle_error("heredoc: failed to read line"));
		}
		if (ft_strcmp(line, delimiter) == 0) // Verifica se o delimitador foi encontrado
		{
			ft_gc_free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		ft_gc_free(line);
	}
	close(pipe_fd[1]); // Fecha o lado de escrita do pipe
	return (pipe_fd[0]); // Retorna o descritor de leitura
}
