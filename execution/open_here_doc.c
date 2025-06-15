/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:01:23 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:40:19 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alnum(char c)
{
	return (is_di(c) || is_al(c));
}

void	sig_heredoc(int signo)
{
	int	i;

	(void)signo;
	write(1, "\n", 1);
	i = 3;
	while (i < 1024)
		close(i++);
	exit(130);
}

static int	open_here_doc_helper(t_here_docc vals, t_exec *head, int *p_fd,
		t_free **free_nodes)
{
	int	status;

	if (vals.pid == 0)
		here_doc_child(head, p_fd, vals.i, free_nodes);
	else
	{
		close(p_fd[1]);
		waitpid(vals.pid, &status, 0);
		if ((WIFEXITED(status) && WEXITSTATUS(status) == 130)
			|| (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
		{
			close(p_fd[0]);
			head->heredoc_fd = -1;
			ft_exit_status(130, 1);
			return (5);
		}
		if (head->heredoc_fd != -1)
			close(head->heredoc_fd);
		head->heredoc_fd = p_fd[0];
	}
	return (0);
}

static t_here_docc	here_docc_init(int pid, int i)
{
	t_here_docc	vals;

	vals.pid = pid;
	vals.i = i;
	return (vals);
}

int	open_here_doc(t_exec *node, t_free **free_nodes)
{
	t_exec	*head;
	int		p_fd[2];
	pid_t	pid;
	int		i;

	head = node;
	if (!head->here_doc || head->len_here_doc == 0)
		return (0);
	1 && (here_doc_limit(head, free_nodes), i = 0);
	while (i < head->len_here_doc)
	{
		if (pipe(p_fd) == -1)
		{
			(close(p_fd[0]), close(p_fd[1]), perror("pipe"));
			return (0);
		}
		pid = fork();
		if (pid == -1)
			(perror("fork"), cleanup_and_exit(free_nodes, 1));
		if (open_here_doc_helper(here_docc_init(pid, i), head, p_fd,
				free_nodes) == 5)
			return (5);
		i++;
	}
	return (0);
}
