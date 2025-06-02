/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:43:03 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/01 18:00:21 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	has_quotes(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			return (1);
		else
			s++;
	}
	return (0);
}

static int	check_access_utils2(char *exp, t_free **free_nodes)
{
	if (access(exp, F_OK) != 0)
		return (print_error(exp, 2, free_nodes), ft_exit_status(1, 1), 0);
	if (access(exp, R_OK) != 0)
		return (perror(exp), ft_exit_status(1, 1), 0);
	return (1);
}

static void	check_access_utils1(t_exec *node, t_files *file, int mode, \
t_access *vars)
{
	if (mode == 0)
	{
		vars->raw = node->infiles_before[vars->inf_i];
		vars->exp = node->infiles[vars->inf_i];
		vars->inf_i++;
	}
	else
	{
		vars->raw = node->outfiles_before[vars->outf_i];
		vars->exp = node->outfiles[vars->outf_i];
		if (file->append)
			vars->flags = O_CREAT | O_WRONLY | O_APPEND;
		else
			vars->flags = O_CREAT | O_WRONLY | O_TRUNC;
		vars->outf_i++;
	}
}

int	check_access(t_exec *node, t_free **free_nodes)
{
	t_files		*files;
	t_access	vars;

	1 && (files = node->files, vars.inf_i = 0, vars.outf_i = 0);
	while (files)
	{
		check_access_utils1(node, files, files->type, &vars);
		if (files->ambiguous && !has_quotes(vars.raw))
			return (print_error(vars.raw, 8, free_nodes),
				ft_exit_status(1, 1), 0);
		if (files->type == 1)
		{
			if (!utils_access_out(&vars, files))
				return (0);
		}
		else
		{
			if (!check_access_utils2(vars.exp, free_nodes))
				return (0);
		}
		files = files->next;
	}
	return (1);
}
