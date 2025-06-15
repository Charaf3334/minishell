/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:51:35 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/14 11:39:14 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	equal_position(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static t_env_ll	*parse_env_str(char *env_str, t_free **free_nodes)
{
	t_env_ll	*node;
	size_t		eq_pos;

	node = create_new_env(free_nodes);
	eq_pos = equal_position(env_str);
	node->key = ft_substr_normal(env_str, 0, eq_pos, free_nodes);
	if (env_str[eq_pos] == '=')
		node->value = ft_substr_normal(env_str, eq_pos + 1, ft_strlen(env_str)
				- eq_pos - 1, free_nodes);
	else
		node->value = NULL;
	return (node);
}

static void	append_env_node(t_env_ll **head, t_env_ll **tail,
		t_env_ll *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

t_env_ll	*extract_ll_env(char **env_strs, t_free **free_nodes)
{
	int			i;
	t_env_ll	*head;
	t_env_ll	*tail;
	t_env_ll	*new_node;

	i = 0;
	head = NULL;
	tail = NULL;
	while (env_strs[i])
	{
		new_node = parse_env_str(env_strs[i], free_nodes);
		append_env_node(&head, &tail, new_node);
		i++;
	}
	return (head);
}
