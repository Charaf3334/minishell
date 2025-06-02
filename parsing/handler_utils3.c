/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:09 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_files(char **str, t_exec *exec, t_free **free_nodes, int *i)
{
	t_cmd_in	vars;

	vars.index = *i;
	handle_files_utils(exec, str, free_nodes, &vars);
}

void	handle_cmds_before(char **before_str, t_exec *exec, t_free **free_nodes,
		int *z)
{
	t_cmd_in	vars;

	init_before(&vars, exec, z, free_nodes);
	while (before_str[vars.index] && ft_strcmp(before_str[vars.index],
			"|") != 0)
	{
		if (ft_strcmp(before_str[vars.index], ">") == 0
			|| ft_strcmp(before_str[vars.index], ">>") == 0)
			vars.index += 2;
		else if (ft_strcmp(before_str[vars.index], "<") == 0)
			vars.index += 2;
		else if (ft_strcmp(before_str[vars.index], "<<") == 0)
			vars.index += 2;
		else
			exec->cmd_before[vars.j_cmd++] = ft_strdup(before_str[vars.index++],
					free_nodes);
	}
}
