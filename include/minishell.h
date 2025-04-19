/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:30:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/19 19:26:36 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// ERROR MACROS -----------


// STRUCTS ----------------
typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_malloc
{
	void			*ptr;
	struct t_malloc	*next;
}	t_malloc;

// FT_MALLOC -----------------
void		*ft_malloc(size_t size);
void		ft_gc_free(void *ptr);
void		ft_gc_exit(void);
t_bool		ft_gc_add(void *ptr);

#endif
