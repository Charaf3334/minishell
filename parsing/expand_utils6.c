/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:05:54 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_new_quote_exp(int start, int end, char c, t_free **free_nodes)
{
	t_quote_exp	*quote_node;

	quote_node = ft_malloc(sizeof(t_quote_exp), free_nodes);
	quote_node->start = start;
	quote_node->end = end;
	quote_node->c = c;
	quote_node->next = NULL;
	return (quote_node);
}

void	append_new_quotes_node(t_quotes_node *info, int start, int end, char c)
{
	t_quote_exp	*node;

	node = ft_new_quote_exp(start, end, c, info->free_nodes);
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

void	ft_exp_quotes(t_quote_exp **head_quote, char *str, t_free **free_nodes)
{
	int				i;
	int				start;
	int				end;
	char			c;
	t_quotes_node	info;

	i = 0;
	info.head = NULL;
	info.curr = NULL;
	info.free_nodes = free_nodes;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			start = i;
			c = str[i++];
			while (str[i] != c)
				i++;
			end = i++;
			append_new_quotes_node(&info, start, end, c);
		}
		else
			i++;
	}
	*head_quote = info.head;
}
