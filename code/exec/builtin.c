/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:03:00 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/08 11:59:00 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	get_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return(1);
	}
	return (0);
}

void	put_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putchar('\n');
		i++;
	}
}

void	put_echo(t_lexer *lexer)
{
	int	newline;
	int	i;

	newline = 1;
	while (lexer->next)
	{
		i = 1;
		if (lexer->next->str[0] == '-' && lexer->next->str[1] == 'n')
			while (lexer->next->str[i] == 'n')
				i++;
		else
			i = 0;
		if (lexer->next->str[i] != '\0')
			break ;
		newline = 0;
		lexer = lexer->next;
	}
	while (lexer->next)
	{
		ft_putstr(lexer->next->str);
		if (lexer->next->next)
			ft_putchar(' ');
		lexer = lexer->next;
	}
	if (newline)
		ft_putchar('\n');
}

int	cd(t_lexer *lexer)
{
	if (!lexer || !lexer->next || !lexer->next->str)
	{
		ft_putstr_fd("path required\n", 2);
		return (1);
	}
	if (chdir(lexer->next->str) != 0)
	{
		perror("cd");
		return(1);
	}
	return(0);
}

int	ft_exit(t_lexer *lexer)
{
	int	exitt;

	ft_putstr("exit\n");
	if (!lexer || !lexer->next)
		exit(0);
	if (is_number(lexer->next->str))
	{
		ft_printf("exit: numeric argument required\n");
		exit (255);
	}
	if (lexer->next->next && lexer->next->next->str)
	{
		ft_printf("exit: too many arguments\n");
		return(1);
	}
	exitt = ft_atoi(lexer->next->str);
	exit(exitt);
}
void	builtin(t_lexer *builtin)
{
	while (builtin)
	{
		if ((builtin->token_type == ECHO))
		{
			put_echo(builtin);
			break ;
		}
		else if (builtin->token_type == CD)
		{
			cd(builtin);
			break;
		}
		else if (builtin->token_type == PWD)
			get_pwd();
		// else if (builtin->token_type == ENV)
		// 	put_env(env);
		else if (builtin->token_type == EXIT)
			ft_exit(builtin);
		// else if (builtin->token_type == EXPORT)
		// {
		// 	export_builtin(builtin);
		// }
		builtin = builtin->next;
	}
}
