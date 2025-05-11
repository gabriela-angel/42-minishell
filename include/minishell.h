/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:30:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/10 21:34:30 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// MACROS ---------------
# define SUCCESS 0

// ERROR MACROS -----------


// STRUCTS ----------------

typedef struct s_token
{
	t_value_type		type;
	char				*value;
	struct s_token	*prev;
	struct s_token	*next;
}						t_token;

typedef struct s_tree
{
	t_token		*token;
	struct s_tree	*left;
	struct s_tree	*right;
}						t_tree;

typedef enum e_value_type
{
	TK_AND = 1,
	TK_OR,
	TK_PIPE,
	TK_OPEN_PARENTHESIS,
	TK_CLOSE_PARENTHESIS,
	TK_REDIR_OUT_APP,
	TK_REDIR_HDOC,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_WORD
}						t_value_type;

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
