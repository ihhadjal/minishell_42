/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:22:24 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstlast(t_list	*lst)
{
	while (lst && lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

// int main(void)
// {
// 	t_list *premier = ft_lstnew("premier");
// 	t_list *deuxieme = ft_lstnew("deuxieme");
// 	t_list *dernier = ft_lstnew("poy feo");
// 	// premier -> next = deuxieme;
// 	// deuxieme -> next = dernier;
// 	ft_lstadd_front(&premier, deuxieme);	
// 	ft_lstlast(premier);
// 	printf("%s", (char *)premier -> content);
// 	free(premier);
// 	free(deuxieme);
// 	free(dernier);
// }