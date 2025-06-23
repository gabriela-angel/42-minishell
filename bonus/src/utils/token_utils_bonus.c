/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/06/23 19:48:32 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	tk_lst_add_back(t_token **head, t_token *new_node)
{
	t_token	*last_node;

	if (!new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
	{
		last_node = get_last_token(*head);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

t_token	*get_last_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ft_cutlist(t_token *start, t_token *end)
{
	t_token	*sublist;
	t_token	*current;

	if (!start)
		return (NULL);
	sublist = start;
	if (sublist->prev)
	{
		sublist->prev->next = NULL;
		sublist->prev = NULL;
	}
	current = start;
	while (current && current != end)
	{
		if (current->next == end && end)
		{
			current->next = NULL;
			break ;
		}
		current = current->next;
	}
	return (sublist);
}

t_token	*search_token_rev(t_token *token_list, t_value_type start_type, \
	t_value_type end_type)
{
	t_token	*current;
	int		parenthesis;

	current = get_last_token(token_list);
	while (current)
	{
		if (current->type >= start_type && current->type <= end_type)
			return (current);
		if (current->type == TK_CLOSE_PARENTHESIS)
		{
			parenthesis = 1;
			while (parenthesis)
			{
				current = current->prev;
				if (current->type == TK_OPEN_PARENTHESIS)
					parenthesis--;
				else if (current->type == TK_CLOSE_PARENTHESIS)
					parenthesis++;
			}
		}
		current = current->prev;
	}
	return (NULL);
}

t_token	*search_token(t_token *token_list, t_value_type start_type, \
	t_value_type end_type)
{
	t_token	*current;
	int		parenthesis;

	current = token_list;
	while (current)
	{
		if (current->type >= start_type && current->type <= end_type)
			return (current);
		if (current->type == TK_OPEN_PARENTHESIS)
		{
			parenthesis = 1;
			while (parenthesis)
			{
				current = current->next;
				if (current->type == TK_CLOSE_PARENTHESIS)
					parenthesis--;
				else if (current->type == TK_OPEN_PARENTHESIS)
					parenthesis++;
			}
		}
		current = current->next;
	}
	return (NULL);
}
