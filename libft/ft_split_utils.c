/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:56:58 by ctoujana          #+#    #+#             */
/*   Updated: 2025/04/23 12:59:21 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	var_set(t_split	*vars)
{
	vars->i = 0;
	vars->count = 0;
	vars->in_s = 0;
	vars->in_d = 0;
	vars->len = 0;
}

int	is_sep(char ch, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (ch == c[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_words(char *str, char *c)
{
	t_split	var;

	var_set(&var);
	while (str[var.i])
	{
		while (str[var.i] && is_sep(str[var.i], c))
			var.i++;
		if (!str[var.i])
			break ;
		var.count++;
		while (str[var.i] && !is_sep(str[var.i], c))
		{
			if ((str[var.i] == '\'' || str[var.i] == '"'))
			{
				1 && (var.quote = str[var.i], var.i++);
				while (str[var.i] && str[var.i] != var.quote)
					var.i++;
				if (str[var.i] == var.quote)
					var.i++;
			}
			else
				var.i++;
		}
	}
	return (var.count);
}

int	get_word_len(char *str, char *c, int *j)
{
	int		len;
	int		i;
	char	quote;
	int		k;

	1 && (len = 0, i = *j);
	while (str[i] && !is_sep(str[i], c))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			k = i + 1;
			while (str[k] && str[k] != quote)
				k++;
			if (str[k] == quote)
				1 && (len += (k - i - 1), i = k + 1);
			else
				1 && (len += (k - i), i = k);
		}
		else
			1 && (len++, i++);
	}
	*j = i;
	return (len);
}
