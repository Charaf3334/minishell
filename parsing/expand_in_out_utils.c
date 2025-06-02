/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_in_out_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/02 12:04:31 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
	return (i);
}

void	ex_utils(t_exp_dollar_var *vars, char **result, t_quotes *context)
{
	if (vars->var_name && !ft_strcmp(vars->var_name, "?"))
	{
		vars->st = ft_exit_status(0, 0);
		vars->status = ft_itoa(vars->st, context->free_nodes);
		*result = ft_strjoin(*result, vars->status, context->free_nodes);
	}
	else if (!vars->var_name)
		*result = ft_strjoin(*result, "$", context->free_nodes);
	else
	{
		set_ambiguous(context->node->files, vars->var_name);
		*result = ft_strjoin(*result, vars->var_value, context->free_nodes);
	}
}

void	expand_dollar_variable2(t_dollar_exp *dollar, char *before_str,
		char **result, t_quotes *context)
{
	t_exp_dollar_var	vars;
	char				**split;

	init_exp(&vars, before_str, dollar, context);
	if (vars.var_value)
		split = ft_split_libft(vars.var_value, " \t\n\v\f\r");
	if (vars.var_value && split && !split[0] && has_only_spaces(vars.var_value))
	{
		set_ambiguous(context->node->files, vars.var_name);
		*result = ft_strjoin(*result, vars.var_value, context->free_nodes);
	}
	if (vars.var_value)
	{
		if (len_strs(split) > 1)
			set_ambiguous(context->node->files, vars.var_name);
		*result = ft_strjoin(*result, vars.var_value, context->free_nodes);
	}
	else if (vars.var_path)
		*result = ft_strjoin(*result, vars.var_path, context->free_nodes);
	else
		ex_utils(&vars, result, context);
}

void	init_exp2(char *quote_type, int *in_quotes,
	t_dollar_exp *dollar, t_quotes *context)
{
	*quote_type = 0;
	*in_quotes = is_in_quotes(dollar->start, context->quote_node, quote_type);
}

void	handle_dollar2(t_dollar_exp *dollar, char *before_str, char **result,
		t_quotes *context)
{
	char	quote_type;
	int		in_quotes;
	char	*dollar_part;
	char	c;
	int		flag;

	init_exp2(&quote_type, &in_quotes, dollar, context);
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
			expand_dollar_variable2(dollar, before_str, result, context);
	}
	else
		expand_dollar_variable2(dollar, before_str, result, context);
}
