/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 10:04:02 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 19:29:52 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (*quote == c)
			*quote = 0;
		else
			*quote = c;
	}
	return (*quote);
}

int	print_quotes(int quotes)
{
	if (quotes == 1)
	{
		ft_putstr_fd("syntax error near unexpected token '''", 2, 1);
		return (1);
	}
	else if (quotes == 2)
	{
		ft_putstr_fd("syntax error near unexpected token '\"'", 2, 1);
		return (1);
	}
	return (0);
}

int	print_redirection(int redirection)
{
	if (redirection == 1)
	{
		ft_putstr_fd("syntax error near unexpected token '>'", 2, 1);
		return (1);
	}
	else if (redirection == 2)
	{
		ft_putstr_fd("syntax error near unexpected token '<'", 2, 1);
		return (1);
	}
	return (0);
}

int	print_pipe(void)
{
	ft_putstr_fd("syntax error near unexpected token '|'", 2, 1);
	return (1);
}

int	check_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
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
		i++;
	}
	if (quote == '\'')
		return (1);
	if (quote == '"')
		return (2);
	return (0);
}
