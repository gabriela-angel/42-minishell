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

static char	*handle_special_cases(char *dollar, char **str, char **after_var,
		char **expanded_var)
{
	if (*(dollar + 1) == '?')
	{
		*expanded_var = ft_itoa(exit_status(-1));
		ft_gc_add(*expanded_var);
		*after_var = ++(*str);
	}
	else if (*(dollar + 1) == '\'' || *(dollar + 1) == '\"')
	{
		*after_var = *str;
		*expanded_var = ft_strdup("");
		ft_gc_add(*expanded_var);
	}
	else
		return (NULL);
	return (*expanded_var);
}

static char	*handle_dollar(char *init_value, char **str, char **env)
{
	char	*dollar;
	char	*before_var;
	char	*after_var;
	char	*expanded_var;
	char	*tmp;

	dollar = (*str)++;
	if (!handle_special_cases(dollar, str, &after_var, &expanded_var))
	{
		while (**str && (ft_isalnum(**str) || **str == '_'))
			(*str)++;
		after_var = *str;
		tmp = ft_substr(dollar, 1, after_var - dollar - 1);
		expanded_var = get_var_from_env(tmp, env);
		free(tmp);
	}
	before_var = ft_substr(init_value, 0, dollar - init_value);
	tmp = ft_strjoin(before_var, expanded_var);
	tmp = ft_strjoin_free(tmp, after_var);
	*str = tmp + ft_strlen(before_var) + ft_strlen(expanded_var) - 1;
	free(before_var);
	ft_gc_add(tmp);
	return (tmp);
}

char	*expand_var(char *str, char **env)
{
	char	*expanded_str;

	expanded_str = str;
	while (*str)
	{
		if (*str == '\'' )
			while (*(++str) && *str != '\'')
				continue ;
		else if (*str == '\"')
		{
			while (*(++str) && *str != '\"')
			{
				if (*str == '$' && str[1] && (ft_isalnum(str[1]) \
					|| ft_strchr("_?", str[1])))
					expanded_str = handle_dollar(expanded_str, &str, env);
			}
		}
		else if (*str == '$' && str[1] && (ft_isalnum(str[1]) \
				|| ft_strchr("_?\'\"", str[1])))
			expanded_str = handle_dollar(expanded_str, &str, env);
		str++;
	}
	return (expanded_str);
}

void	expand_tokens(t_tree *tree)
{
	t_token	*current;
	char	**env;

	current = tree->token;
	env = get_envp(NULL);
	while (current)
	{
		if (current->type == TK_REDIR_HDOC)
		{
			current = current->next->next;
			continue ;
		}
		current->value = expand_var(current->value, env);
		if (!(current->value))
			handle_empty_value(&current, &tree);
		if (ft_strchr_quote_aware(current->value, '*'))
			expand_wildcard(&current, &tree);
		if (ft_strchr_quote_aware(current->value, ' '))
			retokenize(&current);
		current->value = remove_quotes(current->value);
		current = current->next;
	}
}
