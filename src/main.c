#include "minishell.h"

int	main(void)
{
	char		*input;
	t_tk_list	*token_list;
	t_tree		*tree;

	init_environment_variables();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_printf("exit\n");
			break;
		}
		if (input[0] == '\0')
			continue;
		add_history(input);
		token_list = get_token_list(input);
		tree = get_tree(token_list, BRANCH_ROOT);
		if (!tree)
		{
			ft_gc_exit();
			continue;
		}
		free(input);
		ft_gc_exit();
	}
	rl_clear_history();
	return (0);
}
