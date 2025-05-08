/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:30:39 by gangel-a          #+#    #+#             */
/*   Updated: 2025/05/07 14:15:21 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <errno.h>

// MACROS ----------
# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2
# define QUOTE_ERROR "minishell: unclosed quote: `%c'\n"

// ENUMS ----------
typedef enum e_bool
{
    FALSE,
    TRUE
}	t_bool;

typedef enum e_value_type
{
    TK_INVALID,
    TK_OR = 8,
    TK_AND,
    TK_REDIR_HDOC,
    TK_REDIR_OUT_APP,
    TK_WORD,
    TK_PIPE,
    TK_REDIR_IN,
    TK_REDIR_OUT,
    TK_OPEN_PARENTHESIS,
    TK_CLOSE_PARENTHESIS
}	t_value_type;

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
}	t_tree_type;

typedef enum e_tk_hierarchy
{
    TK_CMD_HIERARCHY,
    TK_SUBSHELL_HIERARCHY,
    TK_REDIR_HIERARCHY,
    TK_PIPE_HIERARCHY,
    TK_OR_AND_HIERARCHY
}	t_tk_hierarchy;

typedef enum e_tree_branch
{
    BRANCH_ROOT,
    BRANCH_LEFT,
    BRANCH_RIGHT
}	t_tree_branch;

// STRUCTS ----------
typedef struct s_malloc
{
    void			*ptr;
    struct s_malloc	*next;
}	t_malloc;

typedef struct s_value_part
{
    char				*str;
    char				quote;
}	t_value_part;

typedef struct s_data
{
    t_value_part		*parts;
    size_t				item_no;
    t_bool				error;
}	t_data;

typedef struct s_token
{
    t_value_type		type;
    struct s_token		*file;
    char				*value;
    t_data				data;
}	t_token;

typedef struct s_tk_list
{
    t_token				token;
    struct s_tk_list	*prev;
    struct s_tk_list	*next;
}	t_tk_list;

typedef struct s_tree
{
    t_tree_type		type;
    t_tk_list		*command;
    struct s_tree	*left;
    struct s_tree	*right;
    struct s_tree	*subshell;
    int				here_doc_fd;
    t_tk_list		*file;
}	t_tree;

// Errors (src/utils/error.c) ----------
int			handle_error(char *message);
int			syntax_error(char *token);
int			throw_error(char *cmd_path);
int			signal_error(void);

// Memory Management (src/utils/ft_malloc.c) ----------
void		*ft_malloc(size_t size);
void		ft_gc_free(void *ptr);
void		ft_gc_exit(void);
t_bool		ft_gc_add(void *ptr);

// Environment (src/utils/environ.c) ----------
char		***get_my_env(void);
void		init_environment_variables(void);
void		free_env(void);
void		set_env(char *new_str, char *key, char *value);
void		add_to_env(char *str);
void		update_env(char *new_str, char *key);

// Signals (src/signals/signals.c) ----------
int			setup_signal_handler(void (*func)(int signum));
void		main_signal_handler(int signum);
void		heredoc_signal_handler(int signum);
int			setup_fork_signal_handlers(int pid);

// Executor (src/executor/*.c) ----------
int			executor(t_tree *root);
int			execute_and(t_tree *left, t_tree *right);
int			execute_or(t_tree *left, t_tree *right);
int			execute_pipe(t_tree *left, t_tree *right);
int			execute_redirect(t_tree *left, t_tree *right, int redir_type);
int			execute_command(t_tree *cmd_node);
int			execute_block(t_tree *root);
void		wait_child_status(pid_t pid, int *status);
void		close_pipe(int *pipe_fd);
void		run_command(t_tk_list *tokens);
char		*get_cmd_path(t_tk_list *tokens);
char		*search_in_path(t_tk_list *tokens);
char		**get_cmd_and_args(t_tk_list *tokens);

// Builtins (src/builtin/*.c) ----------
t_bool		is_builtin(t_tk_list *tokens);
int			execute_builtin(t_tree *command_tree);
int			execute_cd(t_tree *command_tree);
int			execute_echo(t_tree *command_tree);
int			execute_env(t_tree *command_tree);
int			execute_exit(t_tree *command_tree);
int			execute_export(t_tree *command_tree);
int			execute_pwd(void);
int			execute_unset(t_tree *command_tree);
char		*get_key(char *arg);
int			is_valid_identifier(char *str, char *cmd_name);
int			is_env_key_present(char *key);
int			is_key_without_value(char *key);
void		print_environ_sorted(void);

// CD Functions (src/builtin/cd.c) ----------
int			change_to_home(void);
int			change_dir(char *path);
int			check_access(char *path);
char		*get_cwd(void);

// Parser (src/parser/*.c) ----------
t_tk_list	*get_next_token(t_tk_list *current, t_tree_branch branch);
int			token_lst_get_size(t_tk_list *token_list);
void		sort_token_lst(t_tk_list **head);
t_tree		*get_tree(t_tk_list *token_list, t_tree_branch branch);
t_bool		is_subshell(t_tk_list *token_list, t_tree_branch branch);
int			compare_priority(t_value_type current, t_value_type priority);
t_tk_list	*get_last_token(t_tk_list *token_list);
t_tk_list	*ft_sublist(t_tk_list *list, t_tk_list *start, t_tk_list *end);
int			create_heredoc(char *delimiter);

// Lexer (src/lexer/*.c) ----------
t_tk_list	*get_token_list(char *input);
char		*handle_word(char *input, t_token *token);
int			ft_isoperator(int c);
int			ft_isredirector(t_token token);
void		set_value(t_token *token);

// Utils (src/utils/helpers.c) ----------
int			*get_exit_status(void);
int			set_exit_status(int status);
int			validate_argument(char *arg);
int			check_limits(char *arg, char sign);

#endif
