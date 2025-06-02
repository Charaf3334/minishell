/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:40:13 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 19:30:44 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipes(char *line)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		if (line[i] == '|' && quote == 0)
			count++;
		i++;
	}
	return (count);
}

int	count_here_doc(char *before_str_joined)
{
	int		count;
	int		i;
	char	*line;
	char	quote;

	count = 0;
	i = 0;
	line = before_str_joined;
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
		else if (line[i] == '<' && line[i + 1] == '<')
			1 && (count++, i += 2);
		else
			i++;
	}
	return (count);
}

void	count_the_length(t_exec *exec, char *line, int *len, int *len_before)
{
	int	i;

	i = 0;
	exec->len_cmds = count_cmds(line);
	exec->len_outfiles = count_outfiles(exec->before_str_joined
			+ (*len_before));
	exec->len_infiles = count_infiles(exec->before_str_joined + (*len_before));
	exec->len_here_doc = count_here_doc(exec->before_str_joined
			+ (*len_before));
	while (line[i] && line[i] != '|')
		i++;
	*len += i;
	if (line[i] == '|')
		(*len)++;
	if (*len_before == 0)
		i = 0;
	else
	{
		i = *len_before;
	}
	while (exec->before_str_joined[i] && exec->before_str_joined[i] != '|')
		i++;
	*len_before += i - *len_before;
	if (exec->before_str_joined[i] == '|')
		(*len_before)++;
}

int	is_quote(char *line, int i, char quote)
{
	if (line[i] == '\'' || line[i] == '"')
	{
		if (quote == 0)
			quote = line[i];
		else if (quote == line[i])
			quote = 0;
	}
	return (quote);
}

int	count_operators(char *line)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (line[i])
	{
		quote = is_quote(line, i, quote);
		if (ft_strchr("><|", line[i]) && quote == 0)
		{
			count++;
			if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<'
					&& line[i + 1] == '<'))
				i++;
		}
		i++;
	}
	return (count);
}
