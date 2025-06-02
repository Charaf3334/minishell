/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:51:17 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:18:35 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*create_new_node(t_free **free_nodes)
{
	t_exec	*new_node;

	new_node = ft_malloc(sizeof(t_exec), free_nodes);
	new_node->cmd = NULL;
	new_node->len_cmds = 0;
	new_node->cmd_before = NULL;
	new_node->infiles = NULL;
	new_node->infiles_before = NULL;
	new_node->len_infiles = 0;
	new_node->last_in = 0;
	new_node->here_doc = NULL;
	new_node->len_here_doc = 0;
	new_node->outfiles = NULL;
	new_node->outfiles_before = NULL;
	new_node->len_outfiles = 0;
	new_node->append = 0;
	new_node->heredoc_fd = -1;
	new_node->next = NULL;
	return (new_node);
}

static void	process_util1(char *s, int *i, int *in_s, int *in_d)
{
	if (s[*i] == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (s[*i] == '"' && !(*in_s))
		*in_d = !(*in_d);
	(*i)++;
}

static void	process_cmd(char *s, int *i, int *in_s, int *in_d)
{
	if (s[*i] == '>' || s[*i] == '<')
	{
		(*i)++;
		if (s[*i] == '>' || s[*i] == '<')
			(*i)++;
		while (s[*i] && is_sep(s[*i], " \t\n\v\f\r"))
			(*i)++;
		while (s[*i] && (*in_s || *in_d || ((!is_sep(s[*i], " \t\n\v\f\r"))
					&& s[*i] != '|' && s[*i] != '>' && s[*i] != '<')))
			process_util1(s, i, in_s, in_d);
	}
	else
	{
		while (s[*i] && (*in_s || *in_d || ((!is_sep(s[*i], " \t\n\v\f\r"))
					&& s[*i] != '|' && s[*i] != '>' && s[*i] != '<')))
			process_util1(s, i, in_s, in_d);
	}
}

int	count_cmds(char *s)
{
	int	count;
	int	i;
	int	in_s;
	int	in_d;

	count = 0;
	i = 0;
	in_s = 0;
	in_d = 0;
	while (s[i])
	{
		while (is_sep(s[i], " \t\n\v\f\r"))
			i++;
		if (!s[i] || s[i] == '|')
			break ;
		if (s[i] != '>' && s[i] != '<')
			count++;
		process_cmd(s, &i, &in_s, &in_d);
	}
	return (count);
}

void	outfile_utils(char *line, int *i, int *count)
{
	if (line[(*i)] == '>')
	{
		if (line[(*i) + 1] == '>')
			(*i)++;
		(*count)++;
		(*i)++;
	}
	else
		(*i)++;
}
