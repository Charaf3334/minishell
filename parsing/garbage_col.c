/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:13:09 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/15 11:42:56 by ctoujana         ###   ########.fr       */
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
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	node->adr = malloc(size);
	if (!node->adr)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	node->next = NULL;
	ft_lstadd_front(free_nodes, node);
	return (node->adr);
}

void	*ft_malloc2(size_t size, t_env **my_env, t_free **free_nodes)
{
	t_free	*node;

	(void)my_env;
	node = malloc(sizeof(t_free));
	if (!node)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	node->adr = malloc(size);
	if (!node->adr)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	node->next = NULL;
	ft_lstadd_front(free_nodes, node);
	return (node->adr);
}
