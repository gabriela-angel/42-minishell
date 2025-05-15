/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesar-m <acesar-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:42:53 by acesar-m          #+#    #+#             */
/*   Updated: 2025/05/14 18:25:41 by acesar-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * Verifica se a string é um identificador válido para export.
 * O primeiro caractere deve ser uma letra ou '_'.
 * Os demais podem ser letras, números ou '_'.
 */
static t_bool	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (FALSE);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * Imprime as variáveis de ambiente no formato do export.
 */
static void	print_variable(char *var)
{
	int	j;

	ft_printf_fd(1, "declare -x ");
	j = 0;
	while (var[j])
	{
		if (var[j] == '=')
		{
			ft_printf_fd(1, "\"%s\"\n", var + j + 1);
			return;
		}
		ft_printf_fd(1, "%c", var[j]);
		j++;
	}
	ft_printf_fd(1, "\n");
}

static void	print_env_sorted(char **env)
{
	int		i;
	char	**copy;

	copy = ft_strdup_split(env);
	if (!copy)
		return;
	ft_sort_strs(copy);
	i = 0;
	while (copy[i])
	{
		print_variable(copy[i]);
		i++;
	}
	ft_free_split(copy);
}

/**
 * Exporta variáveis. Sem argumentos: imprime. Com argumentos: define ou atualiza.
 */
int	exec_export(char **args, char ***env)
{
	int		i;

	if (!args[1])
	{
		print_env_sorted(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "export: `", 9);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
			return (1);
		}
		ft_setenv(args[i], env);
		i++;
	}
	return (0);
}