/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/14 16:15:33 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_exp(t_exp_in_out *vars,
		char *before_str, t_free **free_nodes, t_exec *node)
{
	char			*result;
	int				i;
	t_dollar_exp	*current_dollar;
	t_quotes		context;

	result = ft_strdup("", free_nodes);
	1 && (i = 0, current_dollar = vars->dollar_node);
	context.free_nodes = free_nodes;
	context.quote_node = vars->quote_node;
	context.node = node;
	while (before_str[i])
	{
		if (current_dollar && i == current_dollar->start)
		{
			handle_dollar2(current_dollar, before_str, &result, &context);
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

void	expanding_in_out_helper(t_exp_in_out *vars, t_exec *node,
	t_free **free_nodes, int mode)
{
	int		i;
	t_list	*current;

	i = 0;
	vars->new_len = ft_lstsize_exp(vars->file_list);
	vars->files_array = ft_malloc(sizeof(char *) * (vars->new_len + 1),
			free_nodes);
	current = vars->file_list;
	while (current)
	{
		vars->files_array[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	vars->files_array[i] = NULL;
	if (mode == 0)
	{
		node->infiles = vars->files_array;
		node->len_infiles = vars->new_len;
	}
	else
	{
		node->outfiles = vars->files_array;
		node->len_outfiles = vars->new_len;
	}
}

void	expanding_in_out_init(t_exp_in_out *vars, int i,
	t_free **free_nodes, t_exec *node)
{
	vars->quote_node = NULL;
	vars->dollar_node = NULL;
	ft_exp_quotes(&vars->quote_node, vars->source_array[i], free_nodes);
	ft_exp_dollars(&vars->dollar_node, vars->source_array[i], free_nodes);
	vars->expanded = ft_exp(vars, vars->source_array[i], free_nodes, node);
	vars->was_quoted = has_quote(vars->source_array[i]);
}

void	expanding_in_out(t_exec *node, t_free **free_nodes, int mode)
{
	int				i;
	t_exp_in_out	vars;

	vars.file_list = NULL;
	if (mode == 0)
		vars.source_array = node->infiles_before;
	else
		vars.source_array = node->outfiles_before;
	i = 0;
	while (vars.source_array && vars.source_array[i])
	{
		expanding_in_out_init(&vars, i, free_nodes, node);
		if (vars.was_quoted)
			ft_lstadd_back_exp(&vars.file_list, ft_lstnew_exp(vars.expanded,
					free_nodes));
		else
			add_split_to_list(&vars.file_list, vars.expanded, free_nodes);
		i++;
	}
	expanding_in_out_helper(&vars, node, free_nodes, mode);
}
