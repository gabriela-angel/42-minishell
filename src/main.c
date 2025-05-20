/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:59:42 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/20 17:02:57 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_tree	*tree;
	char	**env;

	(void)argc;
	(void)argv;
	env = ft_strdup_split(envp);
	while (1)
	{
		setup_signals_prompt();
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf_fd(1, "exit\n", 5);
			break ;
		}
		if (exit_status(-1) == 130 && input[0] == '\0')
		{
			ft_gc_free(input);
			ft_gc_exit();
			exit_status(0);
			continue;
		}
		if (input[0])
			add_history(input);
		tokens = get_token_list(input);
		if (tokens)
		{
			tree = get_tree(tokens);
			if (tree)
			{
				expand_tokens(tree);
				minishell_exec(tree, &env);
			}
		}
		ft_gc_free(input);
		ft_gc_exit();
	}
	delete_heredoc();
	ft_free_split(env);
	ft_gc_exit();
	rl_clear_history();
	return (0);
}
