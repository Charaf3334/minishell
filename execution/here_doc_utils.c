/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:09:10 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/01 16:50:35 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_from_here_doc(char *line, int *p_fd, t_exec *head,
	t_free **free_nodes)
{
	if (line)
		free(line);
	close(p_fd[1]);
	cleanup_and_exit(head->my_env, free_nodes, 0);
}

void	handle_fallback(t_exp_here *v, char **new, int *i, t_quotes ctx)
{
	v->raw = ft_substr(v->line, v->start, (*i) - v->start, ctx.free_nodes);
	*new = ft_strjoin(*new, v->raw, ctx.free_nodes);
}

int	fd_return(t_files *files)
{
	int	fd_out;

	if (!files->append)
		fd_out = open(files->file_name, O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	else
		fd_out = open(files->file_name, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	return (fd_out);
}
