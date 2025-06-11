/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:43:12 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/06/11 15:14:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	execute_external_command(t_parser_commands *cmd, t_environnement *mini_env)
{
	int		pid;
	char	**env_array;
	char	*path;

	env_array = env_to_array(mini_env);
	path = find_command_path(cmd->cmd_str[0], mini_env);
	if (!path)
		return (handle_command_not_found(cmd->cmd_str[0], env_array));
	pid = fork();
	if (pid == 0)
		execute_external_child(cmd, path, env_array);
	else if (pid > 0)
		return (wait_for_external_child(pid, path, env_array));
	else
	{
		perror("fork");
		free(path);
		free_env_array(env_array);
		return (1);
	}
	return (0);
}

void	execute_external_child(t_parser_commands *cmd, char *path, char **env_array)
{
	DIR *dir;
	setup_child_signals();
	if (setup_redirections(cmd) == -1)
		exit(1);
	if (access(path, F_OK) == 0)
	{
		dir = opendir(path);
		if (dir != NULL)
		{
			closedir(dir);
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Is a directory", 2);
			exit(126);
		}
		if (access(path, X_OK) != 0)
		{
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Permission denied", 2);
			exit(126);
		}
	}
	execve(path, cmd->cmd_str, env_array);
	perror("execve");
	exit(127);
}

int	wait_for_external_child(int pid, char *path, char **env_array)
{
	int	status;
	int	exit_status;

	ignore_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	free(path);
	free_env_array(env_array);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = 128 + WTERMSIG(status);
	else
		exit_status = 1;
	return (exit_status);
}

int	handle_command_not_found(char *cmd_name, char **env_array)
{
	ft_putstr_fd(cmd_name, 2);
	ft_putendl_fd(": command not found", 2);
	free_env_array(env_array);
	return (127);
}

char	*find_command_path(char *cmd, t_environnement *mini_env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value("PATH", mini_env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = create_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_split_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split_array(paths);
	return (NULL);
}
