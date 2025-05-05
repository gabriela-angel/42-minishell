/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:51:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/19 18:51:12 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*handle_quotes(char *input, t_data	*data)
{
	char	quote;
	size_t	len;

	if (*input != '\'' && *input != '\"')
		return (input);
	quote = *input;
	data->parts = ft_recalloc(data->parts, sizeof(t_value_part) * (data->item_no + 1), sizeof(t_value_part) * data->item_no);
	while (input[len] && input[len] != quote)
		len++;
	data->parts[data->item_no].quote = quote;
	data->parts[data->item_no].str = ft_substr(input, 1, len - 1);
	ft_gc_add(data->parts[data->item_no].str);
	data->item_no++;
	if (!input[len])
	{
		data->error = TRUE;
		return (input + len);
	}
	return (input + len + 1);
}

char	*handle_word(char *input, t_token *token)
{
	t_data	*data;
	size_t	len;

	data = &token->data;
	input = handle_quotes(input, data);
	while (*input && !ft_isspace(*input) && !ft_isoperator(*input))
	{
		data->parts = ft_recalloc(data->parts, sizeof(t_value_part) * (data->item_no + 1), sizeof(t_value_part) * data->item_no);
		len = 0;
		while (input[len] && !ft_isspace(input[len]) && !ft_isoperator(input[len]))
			len++;
		data->parts[data->item_no].str = ft_substr(input, 0, len);
		ft_gc_add(data->parts[data->item_no].str);
		data->item_no++;
		input += len;
		input = handle_quotes(input, data);
	}
	if (!data->error)
		set_value(token);
	token->type = TK_WORD;
	return (input);
}
