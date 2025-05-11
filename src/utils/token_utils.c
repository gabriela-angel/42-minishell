/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:37:12 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/01 13:37:12 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tk_lst_add_back(t_token **head, t_token *new_node)
{
	t_token	*last_node;

	if (!new_node)
		return ;
	if (!(*head))
		*head = new_node;
	else
	{
		last_node = get_last_token(head);
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

t_token	*ft_cpynode(t_token *node)
{
	t_token	*new_node;

	new_node = ft_malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	ft_memmove(&new_node->token, &node->token, sizeof(t_token));
	if (node->token.value)
		new_node->token.value = ft_strdup(node->token.value);
	ft_gc_add(new_node->token.value);
	return (new_node);
}

t_token	*ft_sublist(t_token *list, t_token *start, t_token *end)
{
	t_token	*sublist;
	t_token	*current;
	t_token	*prev;

	sublist = NULL;

	while (list && list != start)
		list = list->next;
	while (list && list != end)
	{
		current = ft_cpynode(list);
		if (!current)
			return (NULL);
		if (!sublist)
			sublist = current;
		else
		{
			prev->next = current;
			current->prev = prev;
		}
		prev = current;
		list = list->next;
	}
	return (sublist);
}
