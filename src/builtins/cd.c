/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:52 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 18:25:59 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Atualiza a variável de ambiente PWD e OLDPWD após mudar de diretório.
 * Você pode ajustar isso para trabalhar com sua própria lista de variáveis se não usar getenv/setenv.
 */
static void	update_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	free(cwd);
}

/**
 * Implementa o comando `cd` com um caminho absoluto ou relativo.
 * - Se nenhum argumento for passado, tenta usar $HOME.
 * - Retorna 1 em caso de erro, 0 em sucesso.
 */
int	exec_cd(char **args)
{
    const char	*path;
    char		*home;

    if (!args[1])
    {
        home = getenv("HOME");
        if (!home)
        {
            ft_printf_fd(2, "cd: HOME not set\n");
            return (1);
        }
        path = home;
    }
    else
        path = args[1];
    if (chdir(path) != 0)
    {
        ft_printf_fd(2, "cd: no such file or directory: %s\n", path);
        return (1);
    }
    update_pwd();
    return (0);
}
