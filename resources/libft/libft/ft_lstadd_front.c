/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihhadjal <ihhadjal@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:00:26 by ihhadjal          #+#    #+#             */
/*   Updated: 2024/12/06 19:09:15 by ihhadjal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res -> content = content;
	res -> next = NULL;
	return (res);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new -> next = *lst;
		*lst = new;
	}
}

// int main(void)
// {
// 	t_list *first = ft_lstnew("premier");
// 	t_list *second = ft_lstnew("deuxieme");
// 	t_list *last = ft_lstnew("dernier");
// 	t_list *nv = ft_lstnew("number 1");
// 	first -> next = second;
// 	second -> next = last;
// 	ft_lstadd_front(&first, nv);
// 	printf("%s",(char *)first -> content);
// 	// free(first);
// 	free(second);
// 	free(last);
// 	free(nv);
// }