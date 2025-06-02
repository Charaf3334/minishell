/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:27:10 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 19:27:56 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variable(char *key, t_env **env)
{
	if (!key)
		return (NULL);
	if (!ft_strcmp(key, "PATH"))
		return ((*env)->default_path[0]);
	return (NULL);
}

int	check_exp(char **str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (str && str[i] && str[i][j])
		{
			if (str[i][j] == '$' && str[i][j + 1] && !is_sep(str[i][j + 1],
					" \t\n\v\f\r"))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_in_quotes(int index, t_quote_exp *quote_node, char *type)
{
	t_quote_exp	*current;

	current = quote_node;
	while (current)
	{
		if (index >= current->start && index <= current->end)
		{
			*type = current->c;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	index_last_quotes(int index, t_quote_exp *quote_node, char *type)
{
	t_quote_exp	*current;

	current = quote_node;
	while (current)
	{
		if (index == current->end)
		{
			*type = current->c;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	handle_regular_chars(char *before_str, int *i,
		char **result, t_quotes *context)
{
	char	quote_type;
	int		in_quotes;

	quote_type = 0;
	in_quotes = is_in_quotes(*i, context->quote_node, &quote_type);
	if (in_quotes)
	{
		if ((quote_type == '\'' && (before_str[*i] == '\''))
			|| (quote_type == '"' && (before_str[*i] == '"')))
		{
			(*i)++;
			return ;
		}
	}
	*result = ft_charjoin(*result, before_str[(*i)++], context->free_nodes);
}
