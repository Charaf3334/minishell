/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/14 16:15:42 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_dollar(t_dollar_exp *dollar, char *before_str, char **result,
		t_quotes *context)
{
	char	quote_type;
	int		in_quotes;
	char	*dollar_part;
	char	c;
	int		flag;

	handle_dollar_init(&quote_type, &in_quotes, dollar, context);
	if (in_quotes && quote_type == '\'')
	{
		dollar_part = ft_substr(before_str, dollar->start, dollar->end
				- dollar->start + 1, context->free_nodes);
		*result = ft_strjoin(*result, dollar_part, context->free_nodes);
	}
	else if (in_quotes && quote_type == '\"')
	{
		dollar_part = ft_substr(before_str, dollar->start, dollar->end
				- dollar->start + 1, context->free_nodes);
		flag = index_last_quotes(dollar->start + 1, context->quote_node, &c);
		if (flag && c == '"')
			*result = ft_strjoin(*result, dollar_part, context->free_nodes);
		else
			expand_dollar_variable(dollar, before_str, result, context);
	}
	else
		expand_dollar_variable(dollar, before_str, result, context);
}

char	*ft_exp(t_expand *vars,
		char *before_str, t_free **free_nodes, t_exec *node)
{
	char			*result;
	int				i;
	t_dollar_exp	*current_dollar;
	t_quotes		context;

	result = ft_strdup("", free_nodes);
	i = 0;
	current_dollar = vars->dollar_node;
	context.free_nodes = free_nodes;
	context.quote_node = vars->quote_node;
	context.node = node;
	while (before_str[i])
	{
		if (current_dollar && i == current_dollar->start)
		{
			handle_dollar(current_dollar, before_str, &result, &context);
			i = current_dollar->end + 1;
			current_dollar = current_dollar->next;
		}
		else
			handle_regular_chars(before_str, &i, &result, &context);
	}
	return (result);
}

static void	add_split_to_list(t_list **cmd_list, char *expanded,
	t_free **free_nodes)
{
	char	**split;
	int		j;

	split = ft_split_quoted(expanded, " \t\n\v\f\r", free_nodes);
	j = 0;
	while (split[j])
	{
		ft_lstadd_back_exp(cmd_list, ft_lstnew_exp(ft_strdup(split[j],
					free_nodes), free_nodes));
		j++;
	}
}

void	expanding_helper(t_expand *vars, t_free **free_nodes, t_exec *node)
{
	t_list	*current;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize_exp(vars->cmd_list);
	vars->cmds = ft_malloc(sizeof(char *) * (len + 1), free_nodes);
	current = vars->cmd_list;
	while (current)
	{
		vars->cmds[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	vars->cmds[i] = NULL;
	node->cmd = vars->cmds;
	node->len_cmds = len;
}

void	expanding(t_exec *node, t_free **free_nodes)
{
	t_expand	vars;
	int			i;

	vars.cmd_list = NULL;
	i = 0;
	while (node->cmd_before[i])
	{
		vars.quote_node = NULL;
		vars.dollar_node = NULL;
		ft_exp_quotes(&vars.quote_node, node->cmd_before[i], free_nodes);
		ft_exp_dollars(&vars.dollar_node, node->cmd_before[i], free_nodes);
		vars.expanded = ft_exp(&vars, node->cmd_before[i], free_nodes, node);
		vars.was_quoted = has_quote(node->cmd_before[i]);
		if (vars.was_quoted)
			ft_lstadd_back_exp(&vars.cmd_list,
				ft_lstnew_exp(vars.expanded, free_nodes));
		else
			add_split_to_list(&vars.cmd_list, vars.expanded, free_nodes);
		i++;
	}
	expanding_helper(&vars, free_nodes, node);
}
