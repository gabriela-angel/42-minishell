/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:46:53 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/19 18:46:53 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int		tk_len(char *input, t_value_type type)
{
	int	len;

	len = 0;
	if (type == TK_WORD)
	{
		while (input[len] && !ft_isspace(input[len])
			&& !ft_isoperator(input[len]))
			len++;
	}
	else if (type == TK_OR || type == TK_AND || type == TK_REDIR_HDOC
		|| type == TK_REDIR_OUT_APP)
		len = 2;
	else
		len = 1;
	return (len);
}

static t_value_type	get_type(char *input)
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
		return (TK_OPEN_PARENTHESIS);
	else if (*input == ')')
		return (TK_CLOSE_PARENTHESIS);
	else if (*input == '\"' || *input == '\''
		|| (!ft_isspace(*input) && !ft_isoperator(*input)))
		return (TK_WORD);
	else
		return (TK_INVALID);
}


t_tk_list	*get_token_list(char *input)
{
	t_tk_list	*head;
	t_tk_list	*current;
	t_tk_list	*prev;

	if (!input || /*check if parenthesis, quotes close*/)
		return (NULL);
	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else
		{
			current = ft_malloc(sizeof(t_tk_list));
			current->type = get_type(input);
			if (current->type == TK_INVALID)
				return (ft_gc_free(current)); // CORRECT THIS WITH ERROR HANDLER
			len = tk_len(input, current->type);
			current->value = ft_substr(input, 0, len);
			tk_lst_add_back(&head, current);
			input += len;
		}
	}
	return (head);
}
