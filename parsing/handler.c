/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:58:52 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/11 11:01:32 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_out_redir(char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>"));
}

static int	is_in_redir(char *s)
{
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, "<<"));
}

static void	handle_out_redir(t_exec *exec, t_free **free_nodes,
	t_cmd_in *vars, int *out_index)
{
	int	arr[2];

	arr[1] = !ft_strcmp(exec->before_str[vars->index], ">>");
	vars->index++;
	arr[0] = 1;
	files_ll(exec, free_nodes, arr, out_index);
}

static void	handle_in_redir(t_exec *exec, t_free **free_nodes,
	t_cmd_in *vars, int *in_index)
{
	int	arr[2];
	int	here_doc;

	here_doc = !ft_strcmp(exec->before_str[vars->index], "<<");
	vars->index++;
	if (exec->before_str[vars->index] && !here_doc)
	{
		arr[0] = 0;
		arr[1] = -1;
		files_ll(exec, free_nodes, arr, in_index);
	}
}

void	handle_files_utils(t_exec *exec, char **str,
	t_free **free_nodes, t_cmd_in *vars)
{
	int	in_index;
	int	out_index;

	in_index = 0;
	out_index = 0;
	while (str[vars->index]
		&& ft_strcmp(exec->before_str[vars->index], "|") != 0)
	{
		if (is_out_redir(exec->before_str[vars->index]))
			handle_out_redir(exec, free_nodes, vars, &out_index);
		else if (is_in_redir(exec->before_str[vars->index]))
			handle_in_redir(exec, free_nodes, vars, &in_index);
		vars->index++;
	}
}
