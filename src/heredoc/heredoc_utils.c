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

static char	*hd_readline(int *save_out)
{
	int		tty_output_fd;
	char	*line;

	*save_out = dup(STDOUT_FILENO);
	tty_output_fd = open("/dev/tty", O_WRONLY | O_NOCTTY);
	if (tty_output_fd >= 0)
	{
		dup2(tty_output_fd, STDOUT_FILENO);
		close(tty_output_fd);
	}
	line = readline("> ");
	dup2(*save_out, STDOUT_FILENO);
	close(*save_out);
	return (line);
}

static int	hd_process_line(char *line, t_here *ctx)
{
	char	*expanded;

	if (!line)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: warning: here-document at line 1 "
			"delimited by end-of-file (wanted `%s`)\n", ctx->end_condition);
		return (SUCCESS);
	}
	ft_gc_add(line);
	if (ft_strcmp(line, ctx->end_condition) == SUCCESS)
	{
		ft_gc_free(line);
		return (SUCCESS);
	}
	if (ctx->is_expandable && ft_strchr(line, '$'))
	{
		expanded = expand_var(line, ctx->env);
		ft_gc_free(line);
		line = expanded;
		ft_gc_add(line);
	}
	ft_printf_fd(ctx->fd, "%s\n", line);
	ft_gc_free(line);
	return (FAILURE);
}

int	write_to_heredoc(int fd, char *end_condition, int is_expandable)
{
	char	*line;
	char	**env;
	int		save_out;
	t_here	ctx;

	env = get_envp(NULL);
	line = hd_readline(&save_out);
	ctx.end_condition = end_condition;
	ctx.is_expandable = is_expandable;
	ctx.env = env;
	ctx.fd = fd;
	return (hd_process_line(line, &ctx));
}

int	*get_heredoc_counter(void)
{
	static int	counter;

	return (&counter);
}
