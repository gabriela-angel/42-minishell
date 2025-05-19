<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:30:09 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/13 23:30:09 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_value_type get_type(char *input);

static int	word_len(char *input)
{
	int	len;

	len = 0;
	while (input[len] && get_type(input + len) == TK_WORD
	&& !ft_isspace(input[len]))
	{
		if (input[len] == '\'')
		{
			len++;
			while (input[len] != '\'')
				len++;
		}
		if (input[len] == '\"')
		{
			len++;
			while (input[len] != '\"')
				len++;
		}
		len++;
	}
	return (len);
}

static int	tk_len(char *input, t_value_type type)
{
	if (type == TK_WORD)
		return (word_len(input));
	else if (type == TK_OR || type == TK_AND || type == TK_REDIR_HDOC
		|| type == TK_REDIR_OUT_APP)
		return (2);
	else
		return (1);
}

static t_value_type	get_type(char *input)
{
	if (*input == '|' && *(input + 1) == '|')
		return (TK_OR);
	else if (*input == '|')
		return (TK_PIPE);
	else if (*input == '&' && *(input + 1) == '&')
		return (TK_AND);
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
	else
		return (TK_WORD);
}


t_token	*get_token_list(char *input)
{
	t_token	*head;
	t_token	*current;
	int		len;

	if (!input || validate_input(input))
	{
		ft_printf_fd(2, "Invalid input: %s\n", input); // Depuração
		return (NULL);
	}
	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else
		{
			current = ft_malloc(sizeof(t_token));
			current->type = get_type(input);
			len = tk_len(input, current->type);
			current->value = ft_substr(input, 0, len);
			tk_lst_add_back(&head, current);
			input += len;
		}
	}
	return (head);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:30:09 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/13 23:30:09 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_value_type	get_type(char *input)
{
	if (*input == '|' && *(input + 1) == '|')
		return (TK_OR);
	else if (*input == '|')
		return (TK_PIPE);
	else if (*input == '&' && *(input + 1) == '&')
		return (TK_AND);
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
	else
		return (TK_WORD);
}

static int	word_len(char *input)
{
	int	len;

	len = 0;
	while (input[len] && get_type(input + len) == TK_WORD
		&& !ft_isspace(input[len]))
	{
		if (input[len] == '\'')
		{
			len++;
			while (input[len] != '\'')
				len++;
		}
		if (input[len] == '\"')
		{
			len++;
			while (input[len] != '\"')
				len++;
		}
		len++;
	}
	return (len);
}

static int	tk_len(char *input, t_value_type type)
{
	if (type == TK_WORD)
		return (word_len(input));
	else if (type == TK_OR || type == TK_AND || type == TK_REDIR_HDOC
		|| type == TK_REDIR_OUT_APP)
		return (2);
	else
		return (1);
}

t_token	*get_token_list(char *input)
{
	t_token		*head;
	t_token		*current;
	int			len;

	if (!input || validate_input(input))
		return (NULL); //create a function to set exit status to SYNTAX ERROR
	head = NULL;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else
		{
			current = ft_malloc(sizeof(t_token));
			current->type = get_type(input);
			len = tk_len(input, current->type);
			current->value = ft_substr(input, 0, len);
			tk_lst_add_back(&head, current);
			input += len;
		}
	}
	return (head);
}
>>>>>>> origin/gabi
