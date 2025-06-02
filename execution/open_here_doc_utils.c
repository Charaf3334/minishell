/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:58:35 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:56 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_here_doc_expand(char **new, int *i, char *line, t_quotes ctx)
{
	t_exp_here	v;

	1 && (v.start = (*i), (*i)++, v.flag = 0, v.line = line);
	if (line[*i] != '?' && !is_alnum(line[*i]) && line[*i] != '_')
		return (*new = ft_charjoin(*new, '$', ctx.free_nodes), 0);
	if (line[(*i)] == '?')
	{
		*new = ft_strjoin(*new, ft_itoa(ft_exit_status(0, 0), ctx.free_nodes),
				ctx.free_nodes);
		return ((*i)++, 0);
	}
	while (line[(*i)] == '"' || line[(*i)] == '\'')
		1 && (v.flag = 1, (*i)++);
	while (is_alnum(line[(*i)]))
		(*i)++;
	v.var_name = ft_substr(line, v.start + 1, *i - v.start - 1, ctx.free_nodes);
	v.value = my_getenv(&ctx, v.var_name);
	v.var_path = expand_variable(v.var_name, ctx.node->my_env);
	if ((!(v.var_path && *v.var_path) && !v.flag) || (v.value && *v.value))
		*new = ft_strjoin(*new, v.value, ctx.free_nodes);
	else if ((!(v.value && *v.value) && !v.flag) || (v.var_path && *v.var_path))
		*new = ft_strjoin(*new, v.var_path, ctx.free_nodes);
	else
		handle_fallback(&v, new, i, ctx);
	return (0);
}

char	*expand_here_doc(char *line, t_free **free_nodes, t_exec *node)
{
	t_quotes	context;
	char		*new;
	int			i;

	1 && (new = NULL, i = 0, context.free_nodes = free_nodes);
	context.node = node;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expand_here_doc_expand(&new, &i, line, context);
			continue ;
		}
		else
			new = ft_charjoin(new, line[i], free_nodes);
		i++;
	}
	return (ft_charjoin(new, '\n', free_nodes));
}

static size_t	copy_quoted_segment(const char *word, char *out, size_t i,
		size_t *j)
{
	char	q;

	if (word[i] == '$')
	{
		q = word[i + 1];
		i += 2;
	}
	else
	{
		q = word[i];
		i++;
	}
	while (word[i] && word[i] != q)
		out[(*j)++] = word[i++];
	if (word[i] == q)
		i++;
	return (i);
}

char	*here_doc_case(char *word, t_free **free_nodes)
{
	size_t	len;
	char	*out;
	size_t	i;
	size_t	j;

	len = ft_strlen(word);
	out = ft_malloc(len + 1, free_nodes);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (word[i] == '$' && (word[i + 1] == '"' || word[i + 1] == '\''))
			i = copy_quoted_segment(word, out, i, &j);
		else if (word[i] == '"' || word[i] == '\'')
			i = copy_quoted_segment(word, out, i, &j);
		else
			out[j++] = word[i++];
	}
	out[j] = '\0';
	return (out);
}

void	here_doc_child(t_exec *head, int *p_fd, int i, t_free **free_nodes)
{
	char	*delimiter;
	char	*line;
	char	*new;

	close(p_fd[0]);
	delimiter = here_doc_case(head->here_doc[i], free_nodes);
	(signal(SIGINT, sig_heredoc), signal(SIGQUIT, SIG_IGN));
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				ft_putstr_fd("warning: here-document delimited \
by end-of-file\n", 2, 0);
			break ;
		}
		new = expand_here_doc(line, free_nodes, head);
		if (ft_strchr(head->here_doc[i], '\'') || ft_strchr(head->here_doc[i],
				'"'))
			new = ft_charjoin(line, '\n', free_nodes);
		write(p_fd[1], new, ft_strlen(new));
		(free(line), line = NULL);
	}
	exit_from_here_doc(line, p_fd, head, free_nodes);
}
