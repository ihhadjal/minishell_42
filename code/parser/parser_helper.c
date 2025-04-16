/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:37:43 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/04/16 11:23:16 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	init_new_cmd(t_mini *mini)
{
	mini->new_cmd->cmd_str = NULL;
	mini->new_cmd->num_redirections = 0;
	mini->new_cmd->hd_file_name = NULL;
	mini->new_cmd->redirections = NULL;
	mini->new_cmd->next = NULL;
	mini->new_cmd->prev = NULL;
}