/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:59:42 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/03 15:43:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(char ***env)
{
	char	*input;
	t_token	*tokens;
	t_tree	*tree;

	while (1)
	{
		setup_signals_prompt();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (exit_status(-1) == 130 && input[0] == '\0')
			exit_status(0);
		else if (input[0])
			add_history(input);
		tokens = get_token_list(input);
		if (tokens && (tree = get_tree(tokens)))
		{
			expand_tokens(tree);
			execute_tree(tree, env);
		}
		ft_gc_free(input);
		ft_gc_exit();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	env = ft_strdup_split(envp);
	shell_loop(&env);
	delete_heredoc();
	ft_free_split(env);
	ft_gc_exit();
	rl_clear_history();
	ft_printf_fd(1, "exit\n", 5);
	return (0);
}
