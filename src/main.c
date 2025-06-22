/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:59:42 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/22 17:45:46 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_loop(void)
{
	char	*input;
	t_token	*tokens;
	t_tree	*tree;

	while (1)
	{
		setup_signals_prompt();
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf_fd(1, "exit\n");
			cleanup_and_exit(EXIT_SUCCESS);
		}
		ft_gc_add(input);
		if (input[0])
			add_history(input);
		tokens = get_token_list(input);
		if (tokens)
		{
			tree = get_tree(tokens);
			if (tree)
				execute_tree(tree);
		}
		ft_gc_exit();
	}
}

char	**get_envp(char **envp)
{
	static char	**env;

	if ((!envp || !*envp) && !env)
		return (NULL);
	if (!envp || !*envp)
		return (env);
	if (env)
		ft_free_matrix(env);
	env = ft_strdup_split(envp);
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	(void)argc;
	(void)argv;
	signal(SIGTSTP, SIG_IGN);
	env = get_envp(envp);
	(void)env;
	shell_loop();
	ft_printf_fd(1, "exit\n");
	cleanup_and_exit(-1);
	return (SUCCESS);
}
