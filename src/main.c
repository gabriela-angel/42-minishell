#include "minishell.h"

int	main(void)
{
	char *input;
	t_tk_list	*token_list;
	t_tree		*tree;

	while (1)
	{
		input = readline("minishell$");
		if (!input)
		{
			printf("exit\n");
			break; //CTRL + D
		}
		if (input[0] == '\0')
			continue;
		add_history(input);
		token_list = get_token_list(input);
		tree = get_tree(token_list);
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
