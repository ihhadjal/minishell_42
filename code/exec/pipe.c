/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:50:11 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/24 19:33:36 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void executor(t_parser_commands *parsed_cmds, t_lexer *built, char **env, t_pipe *pipe)
{
	int	command_count = 0;
	t_parser_commands *current = parsed_cmds;

	while (current)
	{
		command_count++;
		current = current->next;
	}
	if (command_count == 1)
		handle_single_command(parsed_cmds, built, env, pipe);
	
}

void	handle_single_command(t_parser_commands *cmd, t_lexer *built, char **env, t_pipe *pipe)
{
	t_environnement mini_env;
	char *command;
	if (is_builtin(built) == 0)
		builtin(built, &mini_env);
	else if (is_builtin(built) == 1)
	{
		command = find_cmd(env, cmd->cmd_str[0], pipe);
		execute_cmd(cmd, command, env);
		//handle_redirections(cmd->redirections);
	}
}

void	execute_cmd(t_parser_commands *cmd, char *command_path, char **env)
{
	pid_t	pid;
	(void)cmd;
	pid = fork();
	if (pid == 0)
		execve(command_path, cmd->cmd_str, env);
	else
		waitpid(pid, NULL, 0);
}

int	is_builtin(t_lexer *builtin)
{
	if (builtin->token_type == PWD || builtin->token_type == CD 
	|| builtin->token_type == ECHO || builtin->token_type == EXIT 
	|| builtin->token_type == EXPORT || builtin->token_type == UNSET 
	|| builtin->token_type == ENV)
		return(0);
	else
		return (1);
}

char	*search_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P')
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char **env, char *cmd, t_pipe *pipe)
{
	char	**split_path;
	char	*tmp;
	char	*join;
	int		i;

	i = 0;
	pipe->path = search_path(env);
	split_path = ft_split(pipe->path, ':');
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		join = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(join, X_OK) == 0)
		{
			free_string(split_path);
			return (join);
		}
		free(join);
		i++;
	}
	free_string(split_path);
	return (NULL);
}
void	free_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
