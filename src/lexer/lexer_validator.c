/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:31:06 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/22 19:32:01 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char *input, int *i, \
	int *single_quotes, int *double_quotes)
{
	if (input[*i] == '\'')
	{
		(*single_quotes)++;
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
			(*single_quotes)--;
	}
	if (input[*i] == '\"')
	{
		(*double_quotes)++;
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
		if (input[*i] == '\"')
			(*double_quotes)--;
	}
}

int	validate_input(char *input)
{
	int	i;
	int	parenthesis;
	int	single_quotes;
	int	double_quotes;

	i = -1;
	parenthesis = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			check_quotes(input, &i, &single_quotes, &double_quotes);
		if (input[i] == '(')
			parenthesis++;
		else if (input[i] == ')')
			parenthesis--;
	}
	if (parenthesis != 0 || single_quotes != 0 || double_quotes != 0)
	{
		write(STDERR_FILENO, "minishell: invalid syntax, check input \
for open quotes or brackets\n", 67);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
