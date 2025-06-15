/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:25:49 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/15 11:41:16 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_limit(t_exec *head, t_free **free_nodes)
{
	if (head->len_here_doc > 16)
	{
		ft_putstr_fd("maximum here-document count exceeded\n", 2, 0);
		cleanup_and_exit(free_nodes, 2);
	}
}

void	expand_utils_15(t_dollar_exp *dollar, char **result,
	t_quotes *context, t_exp_dollar_var *vars)
{
	if (!(dollar->end - dollar->start) && \
		is_in_quotes2(dollar->start, context->quote_node))
		*result = ft_strjoin(*result, "$", context->free_nodes);
	else if (!(dollar->end - dollar->start) && \
		!vars->before_str[dollar->end + 1])
		*result = ft_strjoin(*result, "$", context->free_nodes);
	else
		*result = ft_strjoin(*result, vars->var_value, context->free_nodes);
}

void	expand_utils_16(t_dollar_exp *dollar, char **result,
	t_quotes *context, t_exp_dollar_var *vars)
{
	if (!(dollar->end - dollar->start) && \
		is_in_quotes2(dollar->start, context->quote_node))
		*result = ft_strjoin(*result, "$", context->free_nodes);
	else if (!(dollar->end - dollar->start) && \
		!vars->before_str[dollar->end + 1])
		*result = ft_strjoin(*result, "$", context->free_nodes);
}

int	is_in_quotes2(int index, t_quote_exp *quote_node)
{
	t_quote_exp	*current;

	current = quote_node;
	while (current)
	{
		if (index > current->start && index < current->end)
			return (1);
		current = current->next;
	}
	return (0);
}
