/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_not_normal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:57:25 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/03 11:37:16 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_quotes(char *str, t_popword	*var, char *word, int *i)
{
	int		found;
	char	quote;
	int		k;

	1 && (quote = str[(*i)], k = (*i) + 1, found = 0);
	while (k < var->end)
	{
		if (str[k] == quote)
		{
			found = 1;
			break ;
		}
		k++;
	}
	if (found)
	{
		(*i)++;
		while ((*i) < k)
			word[var->pos++] = str[(*i)++];
		(*i)++;
	}
	else
		word[var->pos++] = str[(*i)++];
}

static void	init_popword(t_popword	*var, int end)
{
	var->pos = 0;
	var->end = end;
}

static char	*populate_word(int *index, int end, char *str, char *word)
{
	t_popword	var;
	int			i;

	init_popword(&var, end);
	1 && (var.pos = 0, i = *index);
	while (i < end)
	{
		if (str[i] == '\'' || str[i] == '"')
			process_quotes(str, &var, word, &i);
		else
			word[var.pos++] = str[i++];
	}
	1 && (word[var.pos] = '\0', *index = i);
	return (word);
}

static char	*get_word(char *str, int *index, char *c, t_free **free_nodes)
{
	char	*word;
	int		end;
	int		start;

	while (str[*index] && is_sep(str[*index], c))
		(*index)++;
	start = *index;
	end = start;
	word = ft_malloc((get_word_len(str, c, &end) + 1), free_nodes);
	return (populate_word(index, end, str, word));
}

char	**ft_split_not_normal(char *str, char *c, t_free **free_nodes)
{
	char	**split;
	int		words;
	int		i;
	int		index;

	index = 0;
	words = count_words(str, c);
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
