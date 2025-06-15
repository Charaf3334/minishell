/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:52:51 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/15 11:43:13 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_ambiguous(t_files *files, char *name)
{
	t_files	*index;

	index = files;
	while (index)
	{
		if (index->type == 1 && !ft_strcmp(index->file_name + 1, name))
			index->ambiguous = 1;
		else if (index->type == 0 && !ft_strcmp(index->file_name + 1, name))
			index->ambiguous = 1;
		index = index->next;
	}
}

void	init_exp(t_exp_dollar_var *vars, char *before_str,
	t_dollar_exp *dollar, t_quotes *context)
{
	vars->var_name = ft_substr(before_str, dollar->start + 1, dollar->end
			- dollar->start, context->free_nodes);
	vars->var_value = my_getenv(context, vars->var_name);
	vars->var_path = expand_variable(vars->var_name, context->node->my_env);
}

int	utils_access_out(t_access *vars, t_files *files)
{
	vars->fd = open(vars->exp, vars->flags, 0644);
	files->file_name = vars->exp;
	if (vars->fd < 0)
		return (perror(vars->exp), ft_exit_status(1, 1), 0);
	close(vars->fd);
	return (1);
}

int	has_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	not_a_dir(char *cmd, t_exec *head, t_free **free_nodes)
{
	(void)head;
	if (errno == 20)
	{
		print_error(cmd, 7, free_nodes);
		cleanup_and_exit(free_nodes, 126);
	}
}
