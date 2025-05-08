/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:13:22 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/06 15:12:01 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tk_list	*get_next_token(t_tk_list *current, t_tree_branch branch)
{
	if (branch == BRANCH_ROOT || branch == BRANCH_LEFT)
		return (current->prev);
	else
		return (current->next);
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
	if (!new_node->token.value)
	{
		ft_gc_free(new_node);
		return (NULL);
	}
	ft_gc_add(new_node->token.value);
	return (new_node);
}

static void	connect_nodes(t_tk_list **sublist, t_tk_list **prev, t_tk_list *current)
{
	if (!*sublist)
		*sublist = current;
	else
	{
		(*prev)->next = current;
		current->prev = *prev;
	}
	*prev = current;
}

static void	free_sublist(t_tk_list *sublist)
{
	t_tk_list	*temp;

	while (sublist)
	{
		temp = sublist->next;
		ft_gc_free(sublist->token.value);
		ft_gc_free(sublist);
		sublist = temp;
	}
}

t_tk_list	*ft_sublist(t_tk_list *list, t_tk_list *start, t_tk_list *end)
{
	t_tk_list	*sublist = NULL;
	t_tk_list	*current;
	t_tk_list	*prev = NULL;

	if (!list || !start || !end)
		return (NULL);
	t_tk_list *temp = list;
	while (temp && temp != start && temp != end)
		temp = temp->next;
	if (!temp || (temp == end && start != end))
		return (NULL);
	while (list && list != start)
		list = list->next;
	while (list && list != end)
	{
		current = ft_cpynode(list);
		if (!current)
		{
			free_sublist(sublist);
			return (NULL);
		}
		connect_nodes(&sublist, &prev, current);
		list = list->next;
	}
	return (sublist);
}
