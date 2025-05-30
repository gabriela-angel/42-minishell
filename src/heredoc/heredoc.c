/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:01:13 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/15 18:03:04 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lê linhas do terminal até encontrar a condição de término especificada.
// Expande variáveis se necessário e escreve o conteúdo no arquivo temporário.
// Retorna SUCCESS se a condição de término for encontrada, caso contrário FAILURE.
static int	write_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	if (!line)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s`)\n",
			end_condition);
		return (SUCCESS);
	}
	ft_gc_add(line);
	if (ft_strcmp(line, end_condition) == SUCCESS)
	{
		ft_gc_free(line);
		return (SUCCESS);
	}
	if (is_expandable && ft_strchr(line, '$'))
	{
		expanded_line = expand_var(line);
		ft_gc_free(line);
		line = expanded_line;
		ft_gc_add(line);
	}
	ft_printf_fd(fd, "%s\n", line);
	return (FAILURE);
}

// Inicializa o heredoc criando um arquivo temporário para armazenar o conteúdo.
// Define se o heredoc é expansível com base na presença de aspas no token.
// Retorna SUCCESS em caso de sucesso ou FAILURE em caso de erro.
static int	init_heredoc(t_token *token, int *fd, char **file_name,
		t_bool *is_expandable)
{
	int		*heredoc_counter;
	char	*suffix;

	*is_expandable = FALSE;
	heredoc_counter = get_heredoc_counter();
	suffix = ft_itoa((*heredoc_counter)++);
	*file_name = ft_strjoin("/tmp/.heredoc", suffix);
	free(suffix);
	ft_gc_add(*file_name);
	*fd = open(*file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
		return (FAILURE);
	if (!ft_strchr(token->value, '\"') && !ft_strchr(token->value, '\''))
		*is_expandable = TRUE;
	else
		token->value = remove_quotes(token->value);
	return (SUCCESS);
}

// Processo filho responsável por lidar com o heredoc.
// Lê as entradas do usuário, escreve no arquivo temporário e envia o conteúdo para o pipe.
// Finaliza o processo filho após concluir o trabalho.
static int	heredoc_child(t_token *token, int *pipe_fd)
{
	int		fd;
	char	*file_name;
	t_bool	is_expandable;
	char	*end_condition;

	end_condition = token->next->value;
	signal(SIGINT, handle_heredoc_sigint);
	close(pipe_fd[0]);
	if (init_heredoc(token, &fd, &file_name, &is_expandable) != SUCCESS)
		_exit(FAILURE);
	while (42)
	{
		if (write_to_heredoc(fd, end_condition, is_expandable) == SUCCESS)
			break;
	}
	close(fd);
	read_temp_file_and_write_to_pipe(pipe_fd, file_name);
	close(pipe_fd[1]);
	_exit(SUCCESS);
}

// Processo pai que gerencia o heredoc após o término do processo filho.
// Lê o conteúdo do pipe e redireciona a entrada padrão para o pipe.
// Retorna SUCCESS em caso de sucesso ou FAILURE se o processo filho for interrompido.
static int finish_heredoc_parent(int default_stdin, int *pipe_fd, pid_t pid)
{
	int status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) {
		close(pipe_fd[0]);
		dup2(default_stdin, STDIN_FILENO);
		exit_status(130);
		ft_printf_fd(1, "\n");
		return (FAILURE);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	return (SUCCESS);
}

// Função principal para lidar com heredocs.
// Cria um pipe, forka um processo filho para lidar com o heredoc e gerencia o processo pai.
// Retorna SUCCESS em caso de sucesso ou FAILURE em caso de erro.
int handle_heredoc(t_token *token)
{
	int pipe_fd[2];
	pid_t pid;
	int default_stdin = dup(STDIN_FILENO);

	if (pipe(pipe_fd) < 0)
		return (FAILURE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (FAILURE);
	if (pid == 0)
		heredoc_child(token, pipe_fd);
	if (finish_heredoc_parent(default_stdin, pipe_fd, pid))
		return (FAILURE);
	signal(SIGINT, handle_sigint);
	return (SUCCESS);
}
