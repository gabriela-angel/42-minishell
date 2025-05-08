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

void	tk_lst_add_back(t_tk_list **head, t_tk_list *new_node)
{
	t_tk_list	*last_node;

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

t_tk_list	*get_last_token(t_tk_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_tk_list	*ft_cpynode(t_tk_list *node)
{
	t_tk_list	*new_node;

	new_node = ft_malloc(sizeof(t_tk_list));
	if (!new_node)
		return (NULL);
	ft_memmove(&new_node->token, &node->token, sizeof(t_token));
	if (node->token.value)
		new_node->token.value = ft_strdup(node->token.value);
	ft_gc_add(new_node->token.value);
	return (new_node);
}

t_tk_list	*ft_sublist(t_tk_list *list, t_tk_list *start, t_tk_list *end)
{
	t_tk_list	*sublist;
	t_tk_list	*current;
	t_tk_list	*prev;

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
