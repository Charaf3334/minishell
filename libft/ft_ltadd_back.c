/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltadd_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:51:53 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:11 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_ll	*ft_lstlast(t_env_ll *lst)
{
	t_env_ll	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ft_lstadd_back(t_env **my_env, t_env_ll *new)
{
	t_env_ll	*last_node;
	t_env_ll	*lst;

	lst = (*my_env)->env_ll;
	if (!lst || !new)
		return ;
	if (lst == NULL)
		lst = new;
	else
	{
		last_node = ft_lstlast(lst);
		last_node->next = new;
	}
}
