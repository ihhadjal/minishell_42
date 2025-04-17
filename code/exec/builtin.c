/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:03:00 by fakambou          #+#    #+#             */
/*   Updated: 2025/04/16 20:08:03 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

char	*get_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'W')
			return(env[i]);
		i++;
	}
	return (NULL);
}

void	builtin(t_lexer *builtin, char **env)
{
	while(builtin)
	{
		if (builtin->token_type == REDIREC_IN)
			ft_printf("%s\n", get_pwd(env));
		builtin = builtin->next;
	}
}

// int main(int ac, char **av, char **env)
// {
	
// 	(void)av;
// 	if (ac >= 1)
// 		builtin
// 		//printf("%s", get_pwd(env));
// }