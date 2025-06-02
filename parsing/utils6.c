/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:38 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	spaces_utils(char **re, char *line, int *i, int *j)
{
	(*re)[(*j)++] = ' ';
	(*re)[(*j)++] = line[(*i)];
	if ((line[(*i)] == '>' && line[(*i) + 1] == '>') || (line[(*i)] == '<'
			&& line[(*i) + 1] == '<'))
		(*re)[(*j)++] = line[++(*i)];
	(*re)[(*j)++] = ' ';
	(*i)++;
}

char	*add_spaces(char *line, t_free **free_nodes)
{
	int		i;
	int		j;
	char	quote;
	int		op_count;
	char	*re;

	1 && (i = 0, j = 0, quote = 0, op_count = count_operators(line));
	re = ft_malloc(ft_strlen(line) + (op_count * 2) + 1, free_nodes);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
			re[j++] = line[i++];
		}
		else if (ft_strchr("><|", line[i]) && quote == 0)
			spaces_utils(&re, line, &i, &j);
		else
			re[j++] = line[i++];
	}
	re[j] = '\0';
	return (re);
}

int	count_outfiles(char *before_str_joined)
{
	int		count;
	int		i;
	char	*line;
	char	quote;

	1 && (count = 0, i = 0, line = before_str_joined);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				i++;
		}
		else
			outfile_utils(line, &i, &count);
	}
	return (count);
}

static void	infile_utils(char *line, int *count, int *i)
{
	if (line[(*i)] == '<' && line[(*i) + 1] == '<')
		(*i) += 2;
	else if (line[(*i)] == '<')
	{
		(*count)++;
		(*i)++;
	}
	else
		(*i)++;
}

int	count_infiles(char *before_str_joined)
{
	int		count;
	int		i;
	char	*line;
	char	quote;

	1 && (count = 0, i = 0, line = before_str_joined);
	while (line[i] && line[i] != '|')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				i++;
		}
		else
			infile_utils(line, &count, &i);
	}
	return (count);
}
