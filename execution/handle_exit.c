/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:53:27 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:40:05 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_num_long(char *str)
{
	long	val;
	int		j;

	val = ft_atol(str);
	j = 0;
	if (str[j] && str[j] == '+')
		j++;
	while (str[j] && str[j] == '0')
		j++;
	if (val == LONG_MAX && ft_strcmp(&str[j], "9223372036854775807") != 0)
		return (1);
	if (val == LONG_MIN && ft_strcmp(&str[j], "-9223372036854775808") != 0)
		return (1);
	return (0);
}

static int	exit_no_num(char *str)
{
	int	i;

	if (!str || !str[0])
		return (1);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	exit_in_pipeline(t_exec *node, t_free **free_nodes)
{
	char	*arg;

	arg = ft_strtrim(node->cmd[1], " \t\n\v\f\r", free_nodes);
	if (node->len_cmds == 1)
		return (ft_exit_status(0, 1), 1);
	if (exit_no_num(arg))
		(print_error(node->cmd[1], 5, free_nodes), ft_exit_status(2, 1));
	else
	{
		if (node->len_cmds > 2 && !is_num_long(arg))
		{
			ft_putstr_fd("exit: too many arguments\n", 2, 0);
			ft_exit_status(1, 1);
		}
		else if (is_num_long(arg))
		{
			print_error(node->cmd[1], 5, free_nodes);
			ft_exit_status(2, 1);
		}
		else
			ft_exit_status((unsigned char)ft_atol(node->cmd[1]), 1);
	}
	return (1);
}

static int	exit_standalone(t_exec *node, t_free **free_nodes)
{
	char	*arg;

	arg = ft_strtrim(node->cmd[1], " \t\n\v\f\r", free_nodes);
	ft_putstr_fd("exit\n", 1, 0);
	if (node->len_cmds == 1)
		cleanup_and_exit(free_nodes, ft_exit_status(0, 0));
	if (exit_no_num(arg))
	{
		print_error(node->cmd[1], 5, free_nodes);
		cleanup_and_exit(free_nodes, 2);
	}
	if (node->len_cmds > 2 && !is_num_long(arg))
	{
		ft_putstr_fd("exit: too many arguments\n", 2, 0);
		ft_exit_status(1, 1);
		return (1);
	}
	if (is_num_long(arg))
	{
		print_error(node->cmd[1], 5, free_nodes);
		cleanup_and_exit(free_nodes, 2);
	}
	cleanup_and_exit(free_nodes,
		(unsigned char)ft_atol(node->cmd[1]));
	return (1);
}

int	handle_exit(t_exec *node, t_free **free_nodes)
{
	if (node->cmd[0] && !ft_strcmp("exit", node->cmd[0]))
	{
		if (node->nodes_num > 1)
			return (exit_in_pipeline(node, free_nodes));
		return (exit_standalone(node, free_nodes));
	}
	return (0);
}
