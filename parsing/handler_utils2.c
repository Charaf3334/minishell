/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:05 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_cmds_ins(char **str, t_exec *exec, t_free **free_nodes, int *i)
{
	t_cmd_in	vars;

	init(&vars, exec, i, free_nodes);
	while (str[vars.index] && ft_strcmp(exec->before_str[vars.index], "|") != 0)
	{
		if (ft_strcmp(exec->before_str[vars.index], ">") == 0
			|| ft_strcmp(exec->before_str[vars.index], ">>") == 0)
			checker(&vars, i);
		else if (ft_strcmp(exec->before_str[vars.index], "<") == 0)
		{
			vars.index++;
			vars.here_doc = 0;
			if (exec->before_str[vars.index])
				in_doc(str, exec, &vars, free_nodes);
		}
		else if (ft_strcmp(exec->before_str[vars.index], "<<") == 0)
		{
			vars.index++;
			vars.here_doc = 1;
			if (exec->before_str[vars.index])
				in_doc(str, exec, &vars, free_nodes);
		}
		else
			exec->cmd[vars.j_cmd++] = ft_strdup(str[vars.index++], free_nodes);
	}
}

void	handle_in_before(char **before_str, t_exec *exec, t_free **free_nodes,
		int *k3)
{
	int	j;

	j = 0;
	exec->infiles_before = ft_malloc((sizeof(char *)) * (exec->len_infiles + 1),
			free_nodes);
	exec->infiles_before[exec->len_infiles] = NULL;
	while (before_str[(*k3)] && ft_strcmp(before_str[(*k3)], "|") != 0)
	{
		if (!ft_strcmp(before_str[(*k3)], "<"))
		{
			(*k3)++;
			if (before_str[(*k3)])
				exec->infiles_before[j++] = before_str[(*k3)];
		}
		(*k3)++;
	}
}

void	handle_out_before(char **before_str, t_exec *exec, t_free **free_nodes,
		int *k2)
{
	int	j;

	j = 0;
	exec->outfiles_before = ft_malloc((sizeof(char *) * (exec->len_outfiles
					+ 1)), free_nodes);
	exec->outfiles_before[exec->len_outfiles] = NULL;
	while (before_str[(*k2)] && ft_strcmp(exec->before_str[(*k2)], "|") != 0)
	{
		if (!ft_strcmp(before_str[(*k2)], ">")
			|| !ft_strcmp(exec->before_str[(*k2)], ">>"))
			exec->outfiles_before[j++] = ft_strdup(before_str[++(*k2)],
					free_nodes);
		(*k2)++;
	}
}

void	handle_out(char **str, t_exec *exec, t_free **free_nodes, int *i)
{
	int	j;

	j = 0;
	exec->outfiles = ft_malloc((sizeof(char *) * (exec->len_outfiles + 1)),
			free_nodes);
	exec->outfiles[exec->len_outfiles] = NULL;
	while (str[(*i)] && ft_strcmp(exec->before_str[(*i)], "|") != 0)
	{
		if (!ft_strcmp(exec->before_str[(*i)], ">")
			|| !ft_strcmp(exec->before_str[(*i)], ">>"))
		{
			exec->append = 0;
			if (!ft_strcmp(exec->before_str[(*i)], ">>"))
				exec->append = 1;
			exec->outfiles[j++] = ft_strdup(str[++(*i)], free_nodes);
		}
		(*i)++;
	}
}

void	init_before(t_cmd_in *vars, t_exec *x, int *z, t_free **f_nds)
{
	vars->j_cmd = 0;
	vars->index = *z;
	x->cmd_before = ft_malloc((sizeof(char *) * (x->len_cmds + 1)), f_nds);
	x->cmd_before[x->len_cmds] = NULL;
}
