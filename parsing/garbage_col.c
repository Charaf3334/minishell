/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:13:09 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:04 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_free **lst)
{
	t_free	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->adr);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	ft_lstadd_front(t_free **lst, t_free *new)
{
	if (!lst || !new)
		return ;
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	*ft_malloc(size_t size, t_free **free_nodes)
{
	t_free	*node;

	node = malloc(sizeof(t_free));
	if (!node)
	{
		perror("malloc");
		cleanup_and_exit((*free_nodes)->my_env, free_nodes, 0);
	}
	node->adr = malloc(size);
	if (!node->adr)
	{
		perror("malloc");
		cleanup_and_exit((*free_nodes)->my_env, free_nodes, 0);
	}
	node->next = NULL;
	ft_lstadd_front(free_nodes, node);
	return (node->adr);
}

void	*ft_malloc2(size_t size, t_env **my_env, t_free **free_nodes)
{
	t_free	*node;

	node = malloc(sizeof(t_free));
	if (!node)
	{
		perror("malloc");
		cleanup_and_exit(my_env, free_nodes, 0);
	}
	node->adr = malloc(size);
	if (!node->adr)
	{
		perror("malloc");
		cleanup_and_exit(my_env, free_nodes, 0);
	}
	node->next = NULL;
	ft_lstadd_front(free_nodes, node);
	return (node->adr);
}
