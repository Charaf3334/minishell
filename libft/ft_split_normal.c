/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:43:35 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/11 10:58:41 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words1(char *str, char *c)
{
	t_split	var;

	var_set(&var);
	while (str[var.i])
	{
		while (str[var.i] && !var.in_s && !var.in_d && is_sep(str[var.i], c))
			var.i++;
		if (!str[var.i])
			break ;
		var.count++;
		while (str[var.i] && (var.in_s || var.in_d || !is_sep(str[var.i], c)))
		{
			if (str[var.i] == '\'' && !var.in_d)
				var.in_s = !var.in_s;
			else if (str[var.i] == '"' && !var.in_s)
				var.in_d = !var.in_d;
			var.i++;
		}
	}
	return (var.count);
}

static int	get_word_len1(char *str, char *c, int *j)
{
	t_split	vars;

	var_set(&vars);
	while (str[*j] && (vars.in_s || vars.in_d || !is_sep(str[*j], c)))
	{
		if (str[*j] == '\'' && !vars.in_d)
			vars.in_s = !vars.in_s;
		else if (str[*j] == '"' && !vars.in_s)
			vars.in_d = !vars.in_d;
		vars.len++;
		(*j)++;
	}
	return (vars.len);
}

static char	*populate_word(int *index, int j, char *str, char *word)
{
	t_split	vars;

	var_set(&vars);
	while (*index < j)
	{
		word[vars.len++] = str[(*index)++];
	}
	word[vars.len] = '\0';
	return (word);
}

static char	*get_word(char *str, int *index, char *c, t_free **free_nodes)
{
	t_split	vars;
	char	*word;
	int		j;
	int		start;

	var_set(&vars);
	while (str[*index] && is_sep(str[*index], c))
		(*index)++;
	start = *index;
	j = start;
	word = ft_malloc((get_word_len1(str, c, &j) + 1), free_nodes);
	return (populate_word(index, j, str, word));
}

char	**ft_split_normal(char *str, char *c, t_free **free_nodes)
{
	char	**split;
	int		words;
	int		i;
	int		index;

	if (!str)
	{
		split = ft_malloc(sizeof(char *), free_nodes);
		split[0] = NULL;
		return (split);
	}
	index = 0;
	words = count_words1(str, c);
	split = ft_malloc(sizeof(char *) * (words + 1), free_nodes);
	i = 0;
	while (i < words)
	{
		split[i] = get_word(str, &index, c, free_nodes);
		i++;
	}
	split[i] = NULL;
	return (split);
}
