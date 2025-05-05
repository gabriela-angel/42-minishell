/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gangel-a <gangel-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:25:13 by gangel-a          #+#    #+#             */
/*   Updated: 2025/04/24 19:25:13 by gangel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "lexer.h"

// ERROR MACROS -----------


// STRUCTS ----------------

typedef enum e_tree_type
{
	TREE_CMD,
	TREE_SUBSHELL,
	TREE_REDIR_HDOC,
	TREE_REDIR_OUT_APP,
	TREE_REDIR_IN,
	TREE_REDIR_OUT,
	TREE_PIPE,
	TREE_OR,
	TREE_AND
}						t_tree_type;

typedef enum e_tk_hierarchy
{
	TK_CMD_HIERARCHY,
	TK_SUBSHELL_HIERARCHY,
	TK_REDIR_HIERARCHY,
	TK_PIPE_HIERARCHY,
	TK_OR_AND_HIERARCHY
}						t_tk_hierarchy;

typedef enum e_tree_branch
{
	BRANCH_ROOT,
	BRANCH_LEFT,
	BRANCH_RIGHT
}						t_tree_branch;

typedef struct s_tree
{
	t_tree_type		type;
	t_tk_list		*command;
	t_tk_list		*file;
	int				here_doc_fd;
	struct s_tree	*left;
	struct s_tree	*right;
}						t_tree;

// FUNCTIONS -----------------
t_tk_list	*get_token_list(char *input);
char		*handle_word(char *input, t_token *token);

#endif