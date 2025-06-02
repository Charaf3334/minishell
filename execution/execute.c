/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:39:48 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:45 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_here_docs(t_exec *head, int saved_stdin, int saved_stdout,
		t_free **free_nodes)
{
	t_exec	*current;

	current = head;
	while (current)
	{
		if (open_here_doc(current, free_nodes) == 5)
		{
			ft_dup2(saved_stdin, STDIN_FILENO, head->my_env, free_nodes);
			ft_dup2(saved_stdout, STDOUT_FILENO, head->my_env, free_nodes);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	execute_all_nodes(t_exec *head, int nodes_num, t_free **free_nodes)
{
	t_exec	*node;
	int		saved_stdin;
	int		saved_stdout;

	node = head;
	saved_stdin = head->stdin_fd;
	saved_stdout = head->stdout_fd;
	while (node)
	{
		node->stdin_fd = saved_stdin;
		node->stdout_fd = saved_stdout;
		if (execute_nodes(node, nodes_num, free_nodes) == -1)
			break ;
		node = node->next;
		nodes_num--;
	}
}

static t_exec	*last_node_util(t_exec *last_node)
{
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}

int	wait_for_last_child(t_exec *head, int *quit_printed)
{
	t_exec	*last_node;
	int		status;
	int		print_newline;

	1 && (print_newline = 0, last_node = head);
	last_node = last_node_util(last_node);
	if (last_node->exit_flag == 1 && last_node->pid > 0)
	{
		waitpid(last_node->pid, &status, 0);
		if (WIFEXITED(status))
			ft_exit_status(WEXITSTATUS(status), 1);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				print_newline = 1;
			else if (WTERMSIG(status) == SIGQUIT && !(*quit_printed))
			{
				if (head->nodes_num == 1)
					write(1, "Quit (core dumped)\n", 19);
				*quit_printed = 1;
			}
			ft_exit_status(128 + WTERMSIG(status), 1);
		}
	}
	return (print_newline);
}

void	execution(t_exec *head, int nodes_num, t_free **free_nodes)
{
	int	saved_stdin;
	int	saved_stdout;
	int	print_newline;
	int	quit_printed;

	quit_printed = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	head->stdin_fd = saved_stdin;
	head->stdout_fd = saved_stdout;
	if (handle_here_docs(head, saved_stdin, saved_stdout, free_nodes))
		return ;
	execute_all_nodes(head, nodes_num, free_nodes);
	print_newline = wait_for_last_child(head, &quit_printed);
	ft_dup2(saved_stdin, STDIN_FILENO, head->my_env, free_nodes);
	ft_dup2(saved_stdout, STDOUT_FILENO, head->my_env, free_nodes);
	print_newline |= wait_for_childs(&quit_printed, head);
	if (print_newline)
		write(1, "\n", 1);
}
