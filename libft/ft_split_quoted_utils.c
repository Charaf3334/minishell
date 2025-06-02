/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quoted_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:07:33 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/25 15:08:28 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words2(char *str, char *c)
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

int	get_word_len2(char *str, char *c, int *j)
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
				1 && (len += (k - i + 1), i = k + 1);
			else
				1 && (len += (k - i), i = k);
		}
		else
			1 && (len++, i++);
	}
	*j = i;
	return (len);
}
