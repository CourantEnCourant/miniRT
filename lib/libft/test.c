/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:08:54 by weiqi             #+#    #+#             */
/*   Updated: 2026/02/02 20:25:40 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include "libft.h"
//
// int	main(int argc, char *argv[])
// {
// 	t_list	*lst = ft_lstnew(ft_strdup("A new linked list"));
// 	printf("%s\n", (char *)lst->content);
// 	t_list	*new = ft_lstnew(ft_strdup("Node added front"));
// 	ft_lstadd_front(&lst, new);
// 	printf("%s\n", (char *)lst->content);
// 	printf("%d\n", ft_lstsize(lst));
// 	t_list	*last = ft_lstnew(ft_strdup("Node added end"));
// 	ft_lstadd_back(&lst, last);
// 	t_list	*lst_copy = lst;
// 	while (lst_copy->next)
// 		lst_copy = lst_copy->next;
// 	printf("%s\n", (char *)lst_copy->content);
// 	t_list	*waste = ft_lstnew(ft_strdup("Wasted node"));
// 	ft_lstdelone(waste, free);
// 	ft_lstclear(&lst, free);
// }
