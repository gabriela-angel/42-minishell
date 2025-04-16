#include "minishell.h"

int	main(void)
{
	char *input;
	while (1)
	{
		input = readline("minishell$");
		if (!input)
			break; //CTRL + D
		if (*input)
			add_history(input);
		
		free(input);
	}
	rl_clear_history();
	return (0);
}

t_value_type	get_type(char *input)
{
	if (*input == '|' && *(input + 1) == '|')
		return (TK_OR);
	else if (*input == '|')
		return (TK_PIPE);
	else if (*input == '&' && *(input + 1) == '&')
		return (TK_AND);
	else if (*input == '&')
		return (TK_INVALID);
	else if (*input == '<' && *(input + 1) == '<')
		return (TK_REDIR_HDOC);
	else if (*input == '<')
		return (TK_REDIR_IN);
	else if (*input == '>' && *(input + 1) == '>')
		return (TK_REDIR_OUT_APP);
	else if (*input == '>')
		return (TK_REDIR_OUT);
	else if (*input == '(')
		return (TK_OPEN_BRACKET);
	else if (*input == ')')
		return (TK_CLOSE_BRACKET);
	else if (*input == '\"' || *input == '\'' || ft_isalphanum(*input))
		return (TK_WORD); // Handle quotes later
	else
		return (TK_INVALID);
}

char	*tokenize(char *input, t_token *token)
{
	t_value_type	type;

	while (ft_isspace(*input))
		input++;
	type = get_type(input);
	if(type != TK_WORD)
	{
		token->type = type;
	}
	return (input);
}

t_tk_list	*get_token_list(char *input)
{
	t_tk_list	*head;
	t_tk_list	*current;
	t_tk_list	*prev;

	if(!input)
		return (NULL);
	head = NULL;
	while (*input)
	{
		current = ft_malloc(sizeof(t_tk_list));
		if (!head)
			head = current;
		else
		{
			prev->next = current;
			current->prev = prev;
		}
		input = tokenize(input, &current->token);
		prev = current;
	}
	current->next = NULL;
	// if (node->token.data.error)
	// 	return (NULL);
	// init = validate_tokens(init);
	// assign_redirects(init);
	return (head);
}

// if (the token == HEREDOC)
// {
// 	ptr = ft_strdup("");
// 	while (IT IS NOT THE DELIMITOR)
// 	{
// 		ptr = ft_strjoin(ptr, readline(">"));
// 	}
// }