/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:46:58 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 19:33:12 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_new_dollar_exp(int start, int end, t_free **free_nodes)
{
	t_dollar_exp	*dollar_node;

	dollar_node = ft_malloc(sizeof(t_dollar_exp), free_nodes);
	dollar_node->start = start;
	dollar_node->end = end;
	dollar_node->next = NULL;
	return (dollar_node);
}

void	append_new_dollar_node(t_dollar_nodes *info, int start, int end)
{
	t_dollar_exp	*node;

	node = ft_new_dollar_exp(start, end, info->free_nodes);
	if (!info->head)
	{
		info->head = node;
		info->curr = node;
	}
	else
	{
		(info->curr)->next = node;
		info->curr = node;
	}
}

void	init_dollar_node(t_dollar_nodes *info, t_free **free_nodes, int *i)
{
	*i = 0;
	info->head = NULL;
	info->curr = NULL;
	info->free_nodes = free_nodes;
}

void	ft_exp_dollars(t_dollar_exp **head_dollar, char *str,
	t_free **free_nodes)
{
	int				i;
	int				start;
	int				end;
	t_dollar_nodes	info;

	init_dollar_node(&info, free_nodes, &i);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			start = i++;
			if (str[i] && is_al(str[i]))
			{
				while (is_al(str[i]) || is_di(str[i]))
					i++;
			}
			else if (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			end = i - 1;
			append_new_dollar_node(&info, start, end);
		}
		else
			i++;
	}
	*head_dollar = info.head;
}

char	*my_getenv(t_quotes *context, char *key)
{
	t_env_ll	*linked_list;
	t_env_ll	*lst;

	if (!key)
		return (NULL);
	linked_list = (*context->node->my_env)->env_ll;
	lst = linked_list;
	while (lst)
	{
		if (!ft_strcmp(lst->key, key))
			return (ft_strdup(lst->value, context->free_nodes));
		lst = lst->next;
	}
	return (NULL);
}
