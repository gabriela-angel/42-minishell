/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:29:50 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 10:50:29 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_signal_handler(void (*func)(int signum))
{
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;

	ft_bzero(&sigint_action, sizeof(struct sigaction));
	sigint_action.sa_flags = SA_RESTART;
	sigint_action.sa_handler = func;
	ft_bzero(&sigquit_action, sizeof(struct sigaction));
	sigquit_action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sigint_action, NULL) == -1
		|| sigaction(SIGQUIT, &sigquit_action, NULL) == -1)
		return (handle_error("sigaction"));
	return (SUCCESS);
}

void	main_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_exit_status(SIGINT + 128);
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
		set_exit_status(SIGINT + 128);
	}
}

int	setup_fork_signal_handlers(int pid)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_flags = SA_RESTART;
	if (pid == 0)
		action.sa_handler = SIG_DFL;
	else
		action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, NULL) == -1
		|| sigaction(SIGINT, &action, NULL) == -1)
		return (handle_error("sigaction"));
	return (SUCCESS);
}
