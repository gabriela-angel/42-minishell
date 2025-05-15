/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:31:06 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/13 23:31:06 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_quotes(char *input, int *i, int *single_qts, int *double_qts)
{
	if (input[*i] == '\'')
	{
		(*single_qts)++;
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
			(*single_qts)--;
	}
	if (input[*i] == '\"')
	{
		(*double_qts)++;
		(*i)++;
		while (input[*i] && input[*i] != '\"')
			(*i)++;
		if (input[*i] == '\"')
			(*double_qts)--;
	}
}

int	validate_input(char *input)
{
	int	i;
	int	parenthesis;
	int	single_qts;
	int	double_qts;

	i = 0;
	parenthesis = 0;
	single_qts = 0;
	double_qts = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			check_qts(input, &i, &single_qts, &double_qts);
		if (input[i] == '(')
			parenthesis++;
		else if (input[i] == ')')
			parenthesis--;
		i++;
	}
	if (parenthesis != 0 || single_qts != 0 || double_qts != 0)
		return (); //create a function to set exit status to SYNTAX ERROR
	return (SUCCESS);
}
