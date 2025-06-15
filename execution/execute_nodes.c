/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:38:44 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:39:41 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pre_execute_checks(t_exec *node, int nodes_nums, int p_fd[2],
		t_free **free_nodes)
{
	if (pipe(p_fd) == -1)
		return (perror("pipe"), -1);
	if (check_access(node, free_nodes) == 0)
		return (-2);
	open_infile(node, free_nodes);
	if (handle_cd(node, free_nodes))
		return (-2);
	if (handle_exit(node, free_nodes))
		return (-2);
	if (handle_export(node, free_nodes, p_fd, nodes_nums))
		return (-3);
	if (handle_unset(node, free_nodes))
		return (-2);
	return (0);
}

static int	handle_child(t_exec *node, int nodes_nums, int p_fd[2],
		t_free **free_nodes)
{
	signal(SIGQUIT, SIG_DFL);
	close(p_fd[0]);
	if (node->heredoc_fd != -1)
		ft_dup2(node->heredoc_fd, STDIN_FILENO, node->my_env, free_nodes);
	if (nodes_nums > 1)
		ft_dup2(p_fd[1], STDOUT_FILENO, node->my_env, free_nodes);
	if (node->len_outfiles > 0)
	{
		if (open_outfile(node, free_nodes))
			return (close(p_fd[1]), -2);
	}
	else if (nodes_nums == 1)
		ft_dup2(node->stdout_fd, STDOUT_FILENO, node->my_env, free_nodes);
	close(p_fd[1]);
	execute_cmd(node, free_nodes);
	cleanup_and_exit(free_nodes, 0);
	return (0);
}

static int	handle_parent(t_exec *node, int nodes_nums, int p_fd[2],
		t_free **free_nodes)
{
	int	value;

	node->pid = fork();
	if (node->pid == -1)
		return (close(p_fd[0]), close(p_fd[1]), perror("fork"), -1);
	if (node->pid == 0)
	{
		value = handle_child(node, nodes_nums, p_fd, free_nodes);
		if (value != 0)
			return (value);
	}
	else
		execute_nodes_helper(p_fd, nodes_nums, node, free_nodes);
	return (0);
}

int	execute_nodes(t_exec *node, int nodes_nums, t_free **free_nodes)
{
	int	p_fd[2];
	int	value1;
	int	value2;

	node->exit_flag = 0;
	value1 = pre_execute_checks(node, nodes_nums, p_fd, free_nodes);
	if (value1 != 0)
	{
		if (value1 == -2)
		{
			ft_dup2(p_fd[0], 0, node->my_env, free_nodes);
			close(p_fd[1]);
		}
		return (value1);
	}
	node->exit_flag = 1;
	value2 = handle_parent(node, nodes_nums, p_fd, free_nodes);
	if (value2 != 0)
		return (value2);
	return (1);
}
