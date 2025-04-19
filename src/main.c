#include "minishell.h"

int	main(void)
{
	char *input;
	t_tk_list	*token_list;

	while (1)
	{
		input = readline("minishell$");
		if (!input)
			break; //CTRL + D
		if (*input)
			add_history(input);
		token_list = get_token_list(input);
		free(input);
	}

	rl_clear_history();
	ft_gc_exit();
	return (0);
}
