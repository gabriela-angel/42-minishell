/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:33:14 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/08 11:33:23 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tk_list	*token_lst_get_last(t_tk_list *token_list)
{
	t_tk_list	*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	while (current->next)
		current = current->next;
	return (current);
}

t_tk_list	*token_lst_new(char *value, int type)
{
	t_tk_list	*new;
	
	new = ft_malloc(sizeof(t_tk_list));
	if (!new)
	return (NULL);
	new->token.type = type;
	new->token.value = value;
	new->prev = NULL;
	new->next = NULL;
	if (!ft_gc_add(new))
		exit(handle_error("failed to register memory"));
	return (new);
}

void	token_lst_add_back(t_tk_list **token_list, t_tk_list *new)
{
	t_tk_list	*last;

	if (!(*token_list))
		*token_list = new;
	else
	{
		last = token_lst_get_last(*token_list);
		last->next = new;
		new->prev = last;
	}
}

int	token_lst_get_size(t_tk_list *token_list)
{
	t_tk_list	*current;
	int			count;

	count = 0;
	current = token_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	sort_token_lst(t_tk_list **head)
{
	t_tk_list	*current;
	t_tk_list	*next;
	char		*temp;

	current = *head;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->token.value, next->token.value) > 0)
			{
				temp = current->token.value;
				current->token.value = next->token.value;
				next->token.value = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}
