/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:36:46 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/13 23:36:46 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_token *token)
{
	int		default_stdin;
	int		fd;
	char	*file_name;
	bool	is_expandable;

	default_stdin = dup(STDIN_FILENO);

	// these are all functions handled by augusto ------------
	if (setup_signal_handler(heredoc_signal_handler) != SUCCESS)
		return (signal_error());
	//--------------------------------------------------------

	if (init_heredoc(token, &fd, &file_name,
			&is_expandable) != SUCCESS)
		return (set_exit_status(handle_error("failed to create heredoc"))); //create a function to set exit status
	while (42)
		if (write_to_heredoc(fd, token->value, is_expandable) == SUCCESS)
			break ;

	//create a function to set exit status -------------------
	if (*get_exit_status() == SIGINT + 128)
	{
		dup2(default_stdin, STDIN_FILENO);
		return (set_exit_status(SIGINT + 128)); //create a function to set exit status
	}
	//--------------------------------------------------------
	close(fd);
	token->value = file_name;
	return (SUCCESS);
}

int	init_heredoc(t_token *token, int *fd, char **file_name,
		bool *is_expandable)
{
	int		*heredoc_counter;

	*is_expandable = false;
	heredoc_counter = get_heredoc_counter();
	*file_name = ft_strjoin("/tmp/.heredoc", ft_itoa((*heredoc_counter)++));
	*fd = open(*file_name, O_CREAT | O_RDWR | O_TRUNC, 0644); //check this
	if (*fd < 0)
		return (FAILURE);
	if (!ft_strchr(token->value, '\"') && !ft_strchr(token->value, '\''))
		*is_expandable = true;
	else
		token->value = remove_quotes(token->value);
	return (SUCCESS);
}

int	write_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char	*line;

	line = readline("> ");
	//entender oq ta rolando aqui nesse if
	if (!line)
	{
		if (*get_exit_status() != SIGINT + 128)
			ft_fprintf(STDERR_FILENO, "minishell: warning: here-document\
 delimited by end-of-file (wanted '%s')\n", end_condition); //create a function to set exit status
		return (SUCCESS);
	}

	if (ft_strcmp(line, end_condition) == SUCCESS)
		return (SUCCESS);
	if (is_expandable)
		line = expand_var(line); //CREATE A FUNCTION TO EXPAND VARS
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (FAILURE);
}

int	delete_heredoc(void)
{
	char	*file_name;
	int		*heredoc_counter;

	heredoc_counter = get_heredoc_counter();
	while ((*heredoc_counter) >= 0)
	{
		file_name = ft_strjoin("/tmp/.heredoc", ft_itoa((*heredoc_counter)));
		unlink(file_name);
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
