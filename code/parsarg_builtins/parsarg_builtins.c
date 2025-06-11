/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsarg_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:22:20 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 15:58:08 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	execute_parsarg_builtins(t_parser_commands *pars, t_environnement *mini_env,
		t_mini *mini)
{
	t_parser_commands	*current;
	int					i;

	(void)mini;
	i = 0;
	current = pars;
	while (current->cmd_str[i])
	{
		if (!ft_strcmp(current->cmd_str[i], "echo"))
			return (parsarg_echo(&current->cmd_str[i]));
		else if (!ft_strcmp(current->cmd_str[i], "cd"))
			return (parsarg_cd(&current->cmd_str[i]));
		else if (!ft_strcmp(current->cmd_str[i], "pwd"))
			return (parsarg_pwd());
		else if (!ft_strcmp(current->cmd_str[i], "exit"))
			parsarg_exit(&current->cmd_str[i]);
		else if (!ft_strcmp(current->cmd_str[i], "env"))
		{
			print_env(mini_env);
			return (0);
		}
		return (export_and_unset(current, i, mini_env));
		i++;
	}
	return (0);
}

int	parsarg_exit(char **str)
{
	int	exitt;
	int	i;

	i = 1;
	ft_putstr("exit\n");
	if (!str[1])
		exit (0);
	if (str[2])
	{
		ft_putendl_fd(" too many arguments", 2);
		exit (1);
	}
	while (str[i])
	{
		if (is_number(str[i]))
		{
			ft_putendl_fd(" numeric argument required", 2);
			exit (2);
		}
		i++;
	}
	i = 1;
	while (str[i])
		exitt = ft_atoi(str[i++]);
	exit (exitt);
}

int	parsarg_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
	return (1);
}

int	parsarg_cd(char **str)
{
	if (!str[1])
	{
		ft_putstr_fd("path required\n", 2);
		return (1);
	}
	if (str[2])
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	if (chdir(str[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	parsarg_echo(char **str)
{
	int	i;
	int	j;
	int	newline;

	i = 1;
	newline = 1;
	while (str[i] && str[i][0] == '-' && str[i][1] == 'n')
	{
		j = 2;
		while (str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	check_newline(newline);
	return (0);
}
