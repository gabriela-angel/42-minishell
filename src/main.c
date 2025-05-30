/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:59:42 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/30 11:07:39 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Gerencia o loop principal do shell.
// Lê a entrada do usuário, processa tokens, constrói a árvore de comandos e executa.
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
			minishell_exec(tree, env);
		}
		ft_gc_free(input);
		ft_gc_exit();
	}
}

// Função principal.
// Inicializa os recursos, chama o loop principal do shell e finaliza os recursos.
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
