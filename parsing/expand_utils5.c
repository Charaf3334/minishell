/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:05:50 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_dollar_variable(t_dollar_exp *dollar, char *before_str,
		char **result, t_quotes *context)
{
	t_exp_dollar_var	vars;

	vars.var_name = ft_substr(before_str, dollar->start + 1, dollar->end
			- dollar->start, context->free_nodes);
	vars.var_value = my_getenv(context, vars.var_name);
	vars.var_path = expand_variable(vars.var_name, context->node->my_env);
	if (vars.var_value)
		*result = ft_strjoin(*result, vars.var_value, context->free_nodes);
	else if (vars.var_path)
		*result = ft_strjoin(*result, vars.var_path, context->free_nodes);
	else
	{
		if (vars.var_name && !ft_strcmp(vars.var_name, "?"))
		{
			vars.st = ft_exit_status(0, 0);
			vars.status = ft_itoa(vars.st, context->free_nodes);
			*result = ft_strjoin(*result, vars.status, context->free_nodes);
		}
		else if (!vars.var_name && !(before_str + dollar->start + 1)[0])
			*result = ft_strjoin(*result, "$", context->free_nodes);
		else
			*result = ft_strjoin(*result, vars.var_value, context->free_nodes);
	}
}

void	handle_dollar_init(char *quote_type, int *in_quotes,
	t_dollar_exp *dollar, t_quotes *context)
{
	*quote_type = 0;
	*in_quotes = is_in_quotes(dollar->start, context->quote_node, quote_type);
}
