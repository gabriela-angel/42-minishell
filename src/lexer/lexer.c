/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:43 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 13:30:03 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir_file(t_tk_list *node)
{
	t_tk_list	*redir;
	t_tk_list	*file;

	while (node)
	{
		if (ft_isredirector(node->token))
		{
			redir = node;
			file = redir->next;
			redir->token.file = &file->token;
			redir->next = file->next;
			if (file->next)
				file->next->prev = redir;
			file->next = NULL;
			file->prev = NULL;
		}
		node = node->next;
	}
}

void	set_value(t_token *token)
{
	t_data	*data;
	size_t	i;

	data = &token->data;
	i = 0;
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
    if (ft_strncmp(input, "&&", 2) == 0)
        return (TK_AND);
    else if (ft_strncmp(input, "||", 2) == 0)
        return (TK_OR);
    else if (ft_strncmp(input, "|", 1) == 0)
        return (TK_PIPE);
    else if (ft_strncmp(input, "(", 1) == 0)
        return (TK_OPEN_PARENTHESIS);
    else if (ft_strncmp(input, ")", 1) == 0)
        return (TK_CLOSE_PARENTHESIS);
    else if (ft_strncmp(input, ">>", 2) == 0)
        return (TK_REDIR_OUT_APP);
    else if (ft_strncmp(input, "<<", 2) == 0)
        return (TK_REDIR_HDOC);
    else if (ft_strncmp(input, "<", 1) == 0)
        return (TK_REDIR_IN);
    else if (ft_strncmp(input, ">", 1) == 0)
        return (TK_REDIR_OUT);
    else if (ft_isspace(*input))
        return (TK_INVALID);
    else if (*input == '\"' || *input == '\'')
        return (TK_WORD);
    else
        return (TK_WORD);
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
		ft_printf_fd(STDERR_FILENO, QUOTE_ERROR, token->data.parts[token->data.item_no - 1].quote);
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
	if (current->token.data.error)
		return (NULL);
	set_redir_file(head);
	return (head);
}