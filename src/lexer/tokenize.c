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

static void	set_value(t_token *token)
{
	t_data	*data;
	size_t	i;

	data = &token->data;
	len = 0;
	while(i < data->item_no)
	{
		token->value = ft_strjoin(token->value, data->parts[i].str);
		i++;
	}
	ft_gc_free(token->value);
	return ;
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
		return (TK_OPEN_BRACKET);
	else if (*input == ')')
		return (TK_CLOSE_BRACKET);
	else if (*input == '\"' || *input == '\'' || ft_isalphanum(*input))
		return (TK_WORD);
	else
		return (TK_INVALID);
}

static char	*tokenize(char *input, t_token *token)
{
	t_value_type	type;

	while (ft_isspace(*input))
		input++;
	type = get_type(input);
	if (type == TK_INVALID)
	{
		token->type = TK_INVALID;
		token->data.error = 1;
		return (input + 1);
	}
	if (type != TK_WORD)
	{
		token->type = type;
		if (type >= TK_OR && type <= TK_REDIR_OUT_APP)
			return (input + 2);
		return (input + 1);
	}
	input = handle_word(input, token);
	if (token->data.error)
		ft_printf_fd(2, QUOTE_ERROR, token->data.parts[token->data->size - 1].quote); //CHECK THIS
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
	if (current->token.data.error)
		return (NULL);
	// head = validate_tokens(head);
	// assign_redirects(head);
	return (head);
}
