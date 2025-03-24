/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:17:15 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	t_list *lst = ft_lstnew("iheb hadjali");
// 	t_list *kk = ft_lstnew("comment ca va");
// 	ft_lstadd_back(&lst, kk);
// 	int mew = ft_lstsize(lst)	
// 	printf("%d", mew);
// 	// printf("%s\n", (char *)lst -> content)
// 	free(lst);
// 	free(kk);
// 	// free(mew);
// }