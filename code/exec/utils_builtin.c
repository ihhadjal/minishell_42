/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:53 by fakambou          #+#    #+#             */
/*   Updated: 2025/04/23 18:14:43 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

int	is_number(char *str)
{
	int	i;
	
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while(str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}


