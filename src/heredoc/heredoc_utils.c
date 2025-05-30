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

// Remove todos os arquivos temporários de heredoc criados durante a execução.
// Utiliza um contador estático para gerar os nomes dos arquivos e os exclui
// usando a função `unlink`. O contador é decrementado até atingir zero.
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

// Retorna um ponteiro para um contador estático usado para rastrear o número
// de arquivos temporários de heredoc criados. Esse contador é compartilhado
// entre as funções que manipulam heredocs.
int	*get_heredoc_counter(void)
{
	static int	counter;
	return (&counter);
}

// Lê o conteúdo de um arquivo temporário de heredoc e escreve no pipe fornecido.
// Abre o arquivo em modo somente leitura, lê os dados em blocos de 1024 bytes
// e os escreve no descritor de escrita do pipe.
void	read_temp_file_and_write_to_pipe(int *pipe_fd, char *file_name)
{
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd >= 0)
	{
		while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
			write(pipe_fd[1], buffer, bytes_read);
		close(fd);
	}
}
