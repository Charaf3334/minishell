/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:30:01 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 19:30:02 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	utils1_red(char *line, int *i, int *flag)
{
	int	j;

	if (line[(*i) + 1] == '>' || line[(*i) + 1] == '<')
	{
		if (line[(*i) + 1] != line[*i])
			*flag = 1;
		else
			(*i)++;
	}
	j = (*i) + 1;
	while (line[j] && is_sep(line[j], " \t\n\v\f\r"))
		j++;
	if (!line[j] || line[j] == '>' || line[j] == '<' || line[j] == '|'
		|| line[j] == '#' || line[j] == '&' || line[j] == ';')
		*flag = 1;
	*i = j - 1;
}

int	ret_value(int flag, char last_redir)
{
	if (flag)
	{
		if (last_redir == '>')
			return (1);
		if (last_redir == '<')
			return (2);
	}
	return (0);
}

int	invalid_redirection(char *line)
{
	int		i;
	char	quote;
	char	last_redir;
	int		flag;

	i = 0;
	quote = 0;
	last_redir = 0;
	flag = 0;
	while (line[i])
	{
		quotes(line[i], &quote);
		if (!quote && (line[i] == '>' || line[i] == '<'))
		{
			last_redir = line[i];
			utils1_red(line, &i, &flag);
		}
		i++;
	}
	if (ret_value(flag, last_redir))
		return (ret_value(flag, last_redir));
	return (0);
}

void	utils1_pipe(char *line, int *i, int *flag)
{
	int	j;

	if ((*i) == 0 && line[*i] == '|')
		*flag = 1;
	else if (line[*i] == '|')
	{
		j = (*i) + 1;
		while (line[j] && is_sep(line[j], " \t\n\v\f\r"))
			j++;
		if (!line[j] || line[j] == '|')
			*flag = 1;
	}
}

int	invalid_pipe(char *line)
{
	int		i;
	char	quote;
	int		flag;

	i = 0;
	quote = 0;
	flag = 0;
	while (line[i])
	{
		quotes(line[i], &quote);
		if (!quote)
			utils1_pipe(line, &i, &flag);
		i++;
	}
	if (flag)
		return (1);
	return (0);
}
