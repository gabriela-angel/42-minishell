/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:12:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/16 20:12:39 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	new_str = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && quote == str[i])
			quote = '\0';
		else if ((str[i] == '\'' || str[i] == '\"') && quote == '\0')
			quote = str[i];
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	handle_empty_value(t_token **current, t_tree **tree)
{
	if ((*current)->prev)
		(*current)->prev->next = (*current)->next;
	if ((*current)->next)
		(*current)->next->prev = (*current)->prev;
	if (*((*tree)->token->value) == '\0')
	{
		(*tree)->token = (*tree)->token->next;
		if ((*tree)->token)
			(*tree)->token->prev = NULL;
	}
}

char	*ft_strchr_quote_aware(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	retokenize(t_token **token)
{
	t_token	*next;
	t_token	*current;
	char	**tk_lst;
	int		i;
	int		len;

	current = *token;
	next = (*token)->next;
	tk_lst = ft_split((*token)->value, ' ');
	if (*tk_lst)
	{
		(*token)->value = *tk_lst;
		i = 0;
		while (tk_lst[++i])
		{
			(*token)->next = new_token(tk_lst[i], &len);
			(*token)->next->prev = (*token);
			(*token) = (*token)->next;
		}
		(*token)->next = next;
		(*token) = current;
	}
	else
		(*token)->value = "\0";
	ft_free_matrix(tk_lst);
}
