/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:53 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/07 11:04:21 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	allocate_new_part(t_data *data)
{
	t_value_part	*new_parts;

	new_parts = ft_malloc(sizeof(t_value_part) * (data->item_no + 1));
	if (!new_parts)
		exit(handle_error("Memory allocation failed"));
	if (data->parts)
	{
		ft_memcpy(new_parts, data->parts, sizeof(t_value_part) * data->item_no);
		ft_gc_free(data->parts);
	}
	data->parts = new_parts;
}

static void	add_part(t_data *data, char *str, char quote)
{
	allocate_new_part(data);
	data->parts[data->item_no].quote = quote;
	data->parts[data->item_no].str = str;
	if (!ft_gc_add(str))
		exit(handle_error("Memory registration failed"));
	data->item_no++;
}

static char	*process_quotes(char *input, t_data *data)
{
	char	quote;
	size_t	len;
	char	*str;

	if (*input != '\'' && *input != '\"')
		return (input);
	quote = *input;
	len = 1;
	while (input[len] && input[len] != quote)
		len++;
	str = ft_substr(input, 1, len - 1);
	if (!str)
		exit(handle_error("Memory allocation failed"));
	add_part(data, str, quote);
	if (!input[len])
	{
		data->error = TRUE;
		return (input + len);
	}
	return (input + len + 1);
}

static char	*process_word_part(char *input, t_data *data)
{
	size_t	len;
	char	*str;

	len = 0;
	while (input[len] && !ft_isspace(input[len]) && !ft_isoperator(input[len]))
		len++;
	str = ft_substr(input, 0, len);
	if (!str)
		exit(handle_error("Memory allocation failed"));
	add_part(data, str, 0);
	return (input + len);
}

char	*handle_word(char *input, t_token *token)
{
	t_data	*data;

	data = &token->data;
	input = process_quotes(input, data);
	while (*input && !ft_isspace(*input) && !ft_isoperator(*input))
	{
		input = process_word_part(input, data);
		input = process_quotes(input, data);
	}
	if (!data->error)
		set_value(token);
	token->type = TK_WORD;
	return (input);
}
