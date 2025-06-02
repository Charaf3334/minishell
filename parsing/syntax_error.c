/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:29:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 19:29:43 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstlast_exp(t_list *lst)
{
	t_list	*node;

	if (!lst)
		return (NULL);
	node = lst;
	while (node->next != NULL)
		node = node->next;
	return (node);
}

int	check_syntax(char *line)
{
	int	quotes;
	int	pipe;
	int	redirection;

	quotes = check_quotes(line);
	pipe = invalid_pipe(line);
	redirection = invalid_redirection(line);
	if (quotes)
	{
		ft_exit_status(2, 1);
		return (print_quotes(quotes));
	}
	if (pipe)
	{
		ft_exit_status(2, 1);
		return (print_pipe());
	}
	if (redirection)
	{
		ft_exit_status(2, 1);
		return (print_redirection(redirection));
	}
	return (0);
}
