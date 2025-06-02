/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/02 11:12:03 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	files_ll_init(t_files *file)
{
	file->file_name = NULL;
	file->type = 0;
	file->ambiguous = 0;
	file->append = 0;
}

void	files_ll(t_exec *x, t_free **f_nds, int arr[], int *index)
{
	t_files	*new_file;
	t_files	*current;
	int		flag;

	flag = arr[0];
	if ((!flag && *index >= x->len_infiles) || \
		(flag && *index >= x->len_outfiles))
		return ;
	new_file = ft_malloc(sizeof(t_files), f_nds);
	files_ll_init(new_file);
	if (!flag)
		new_file->file_name = x->infiles[*index];
	else
		new_file->file_name = x->outfiles[*index];
	new_file->type = flag;
	1 && (new_file->append = arr[1], (*index)++, new_file->next = NULL);
	if (x->files == NULL)
		x->files = new_file;
	else
	{
		current = x->files;
		while (current->next != NULL)
			current = current->next;
		current->next = new_file;
	}
}

void	init(t_cmd_in *vars, t_exec *x, int *i, t_free **f_nds)
{
	vars->j_cmd = 0;
	vars->j_in = 0;
	vars->j_here = 0;
	vars->index = *i;
	vars->flag = 0;
	x->cmd = ft_malloc((sizeof(char *) * (x->len_cmds + 1)), f_nds);
	x->infiles = ft_malloc((sizeof(char *) * (x->len_infiles + 1)), f_nds);
	x->here_doc = ft_malloc((sizeof(char *) * (x->len_here_doc + 1)), f_nds);
	x->files = NULL;
	x->cmd[x->len_cmds] = NULL;
	x->infiles[x->len_infiles] = NULL;
	x->here_doc[x->len_here_doc] = NULL;
}

void	in_doc(char **str, t_exec *exec, t_cmd_in *vars, t_free **f_nds)
{
	if (!vars->here_doc)
	{
		exec->last_in = 0;
		exec->infiles[vars->j_in++] = ft_strdup(str[vars->index++], f_nds);
	}
	else
	{
		exec->last_in = 1;
		exec->here_doc[vars->j_here++] = ft_strdup(exec->before_str
			[vars->index++], f_nds);
	}
}

void	checker(t_cmd_in *vars, int *i)
{
	if (vars->flag == 0)
	{
		*i = vars->index;
		vars->flag = 1;
	}
	vars->index += 2;
}
