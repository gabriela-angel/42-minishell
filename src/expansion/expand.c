/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:08:44 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/16 20:08:44 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//get_exit_status

// Handles special cases for variable expansion such as : $? (last exit status) and quotes
char	*handle_special_cases(char *dollar, char **str, char **after_var,
		char **expanded_var)
{
	if (*(dollar + 1) == '?')
	{
		*expanded_var = ft_itoa(*get_exit_status());
		*after_var = ++(*str);
	}
	else if (*(dollar + 1) == '\'' || *(dollar + 1) == '\"')
	{
		*after_var = *str;
		*expanded_var = ft_strdup("");
	}
	else
		return (NULL);
	return (*expanded_var);
}

char	*handle_dollar(char *init_value, char **str)
{
	char	*dollar;
	char	*before_var;
	char	*after_var;
	char	*expanded_var;
	char	*result;

	dollar = (*str)++;
	if (!handle_special_cases(dollar, str, &after_var, &expanded_var))
	{
		while (**str && (ft_isalnum(**str) || **str == '_'))
			(*str)++;
		after_var = *str;
		expanded_var = getenv(ft_substr(dollar, 1, after_var - dollar - 1));
	}
	before_var = ft_substr(init_value, 0, dollar - init_value);
	result = ft_strjoin(before_var, expanded_var);
	result = ft_strjoin_free(result, after_var);
	*str = result + ft_strlen(before_var) + ft_strlen(expanded_var) - 1;
	free(before_var);
	free(expanded_var);
	ft_gc_add(result);
	return (result);
}

char	*expand_var(char *str)
{
	char	*expanded_str;

	expanded_str = str;
	while (str)
	{
		if (*str == '\'' )
			while (*(++str) && *str != '\'')
				continue;
		else if (*str == '\"')
		{
			while (*(++str) && *str != '\"')
			{
				if (*str == '$' && str[1] && (ft_isalnum(str[1])
						|| ft_strchr("_?", str[1])))
					expanded_str = handle_dollar(expanded_str, &str);
			}
		}
		else if (*str == '$' && str[1] && (ft_isalnum(str[1])
					|| ft_strchr("_?\'\"", str[1])))
			expanded_str = handle_dollar(expanded_str, &str);
		str++;
	}
	return (expanded_str);
}

void	expand_tokens(t_tree *tree)
{
	t_token	*current;

	current = tree->token;
	while (current)
	{
		current->value = expand_var(current->value);
		if (!(current->value))
			handle_empty_value(&current, &tree);
		if (ft_strchr_quote_aware(current->value, '*'))
			expand_wildcards(&current, &tree);
		if (ft_strchr_quote_aware(current->value, ' '))
			retokenize(&current);
		current->value = remove_quotes(current->value);
		current = current->next;
	}
}
