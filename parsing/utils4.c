/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:28 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_init(t_exec **current, t_vals *v, t_free **fnds, t_env **my_env)
{
	(*current)->nodes_num = v->nodes_num;
	(*current)->my_env = my_env;
	(*current)->before_str = v->before_str;
	(*current)->before_str_joined = ft_join_strs(v->before_str, fnds);
}

void	expand_if_possible(t_exec **current, t_free **free_nodes)
{
	if (check_exp((*current)->cmd_before, (*current)->len_cmds))
		expanding((*current), free_nodes);
	if (check_exp((*current)->infiles_before, (*current)->len_infiles))
		expanding_in_out((*current), free_nodes, 0);
	if (check_exp((*current)->outfiles_before, (*current)->len_outfiles))
		expanding_in_out((*current), free_nodes, 1);
}

void	init_process_loop(t_vals *v, t_exec **head, t_exec **current,
	t_free **free_nodes)
{
	append_new_node(head, current, free_nodes);
	exec_init(current, v, free_nodes, v->my_env);
	count_the_length(*current, v->fix_spaces + v->len_line,
		&v->len_line, &v->len_before);
	v->z = v->i;
	v->k = v->i;
	v->k2 = v->i;
	v->k3 = v->i;
}

void	handle_redirections(t_vals *v, t_exec *current, t_free **free_nodes)
{
	handle_cmds_before(v->before_str, current, free_nodes, &v->z);
	handle_cmds_ins(v->str, current, free_nodes, &v->i);
	handle_in_before(v->before_str, current, free_nodes, &v->k3);
	handle_out_before(v->before_str, current, free_nodes, &v->k2);
	handle_out(v->str, current, free_nodes, &v->i);
	handle_files(v->str, current, free_nodes, &v->k);
	expand_if_possible(&current, free_nodes);
}

void	process_loop(t_vals *v, t_exec **head, t_exec **current,
	t_free **free_nodes)
{
	while (v->j)
	{
		init_process_loop(v, head, current, free_nodes);
		handle_redirections(v, *current, free_nodes);
		v->i++;
		v->j--;
	}
}
