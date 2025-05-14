/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakambou <fakambou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:05:15 by fakambou          #+#    #+#             */
/*   Updated: 2025/05/13 19:19:29 by fakambou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	redirect_in(t_lexer *redirect)
{
	if (redirect->token_type == REDIREC_IN)
	{
		redirect->next->str 
	}
}