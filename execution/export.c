/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:42:33 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/14 11:45:47 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_identifier(char *ident)
{
	int	i;

	if (!(is_al(ident[0]) || ident[0] == '_'))
		return (1);
	i = 1;
	while (ident[i])
	{
		if (ident[i] == '=')
			break ;
		if (ident[i] == '+')
		{
			if (ident[i + 1] == '=')
				return (2);
			return (1);
		}
		if (!is_di(ident[i]) && !is_al(ident[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	handle_export_arg(t_exec *head, t_free **free_nodes, \
char *cmd, int *exit)
{
	int	mode;

	mode = check_valid_identifier(cmd);
	if (mode == 1)
	{
		print_error(cmd, 6, free_nodes);
		*exit = 1;
		return ;
	}
	if (head->nodes_num > 1)
		return ;
	if (mode == 2)
		export_append_value(head, free_nodes, cmd);
	else if (!ft_strchr(cmd, '='))
		export_no_value(head, cmd, free_nodes);
	else
		export_normal_assign(head, free_nodes, cmd);
}

int	handle_export(t_exec *node, t_free **free_nodes, int *p_fd, int nodes_nums)
{
	t_exec	*head;
	int		i;
	int		exit;

	head = node;
	if (!head->cmd[0] || ft_strcmp(head->cmd[0], "export") != 0)
		return (0);
	if (head->len_cmds == 1)
		handle_export_no_args(head, free_nodes, p_fd, nodes_nums);
	else
	{
		ft_dup2(p_fd[0], STDIN_FILENO, node->my_env, free_nodes);
		close(p_fd[1]);
		i = 1;
		exit = 0;
		while (i < head->len_cmds)
		{
			handle_export_arg(head, free_nodes, head->cmd[i], &exit);
			i++;
		}
		ft_exit_status(exit, 1);
	}
	return (1);
}

int	handle_unset(t_exec *head, t_free **free_nodes)
{
	int	i;

	if (!head->cmd[0] || ft_strcmp(head->cmd[0], "unset") != 0)
		return (0);
	if (head->nodes_num > 1)
	{
		ft_exit_status(0, 1);
		return (1);
	}
	i = 1;
	while (i < head->len_cmds)
	{
		free_and_delete_node(&((*head->my_env)->env_ll), head->cmd[i], head);
		refresh_env_strs(head, free_nodes);
		i++;
	}
	ft_exit_status(0, 1);
	return (1);
}
