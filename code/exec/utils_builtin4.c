/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:14:26 by ihhadjal          #+#    #+#             */
/*   Updated: 2025/05/27 15:35:05 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../resources/minishell.h"

void	name_swap(t_environnement *current, char *temp_name)
{
	current->variable_name = current->next->variable_name;
	current->next->variable_name = temp_name;
}

t_environnement	*add_argument_to_env(t_lexer *builtin)
{
	t_environnement	*new_argument_node;
	char			*temp;
	char			*equal_sign;
	int				name_lenght;

	new_argument_node = malloc(sizeof(t_environnement));
	if (!new_argument_node)
		return (NULL);
	equal_sign = ft_strchr(builtin->str, '=');
	if (equal_sign)
	{
		name_lenght = equal_sign - builtin->str + 1;
		temp = ft_substr(builtin->str, 0, name_lenght);
		new_argument_node->variable_name = ft_strdup(temp);
		free(temp);
		new_argument_node->variable_value = ft_strdup(equal_sign + 1);
	}
	else
	{
		free(new_argument_node);
		return (NULL);
	}
	new_argument_node->next = NULL;
	return (new_argument_node);
}

int	error_print(t_lexer *builtin)
{
	ft_putstr_fd("export : ", 2);
	print_error(builtin->next->str, ": not a valid identifier");
	return (1);
}

int	is_valid_export_argument(char *str, int name_length)
{
	if (!str || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	if (ft_symbols(ft_substr(str, 0, name_length)) != 0)
		return (0);
	return (1);
}

int	ft_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 33 && str[i] <= 47) || (str[i] >= 58 && str[i] <= 60)
			|| (str[i] >= 91 && str[i] <= 94) || (str[i] == 96)
			|| (str[i] >= 123 && str[i] <= 126) || (str[i] >= 62
				&& str[i] <= 63))
			return (1);
		i++;
	}
	return (0);
}
