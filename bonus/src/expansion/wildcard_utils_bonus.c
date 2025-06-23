/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:16:50 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/18 16:16:50 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	alpha_sort_lst(t_token **head)
{
	t_token	*current;
	t_token	*next;
	char	*temp;

	current = *head;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->value, next->value) > 0)
			{
				temp = current->value;
				current->value = next->value;
				next->value = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}

void	update_tk_lst(t_token **token, t_token *match_lst)
{
	t_token	*last;

	last = get_last_token(match_lst);
	last->next = (*token)->next;
	if ((*token)->next)
		(*token)->next->prev = last;
	match_lst->prev = (*token)->prev;
	if ((*token)->prev)
		(*token)->prev->next = match_lst;
	*token = last;
}

void	create_match_lst(t_token **head, char *data)
{
	t_token	*last_node;
	t_token	*new_node;

	new_node = ft_malloc(sizeof(t_token));
	new_node->type = TK_WORD;
	new_node->value = ft_strdup(data);
	ft_gc_add(new_node->value);
	if (!(*head))
		*head = new_node;
	else
	{
		last_node = get_last_token(*head);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}
