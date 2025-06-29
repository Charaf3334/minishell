/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/15 11:38:29 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_generator(char **env, t_free **free_nodes)
{
	t_env	*my_env;

	my_env = malloc(sizeof(t_env));
	if (!my_env)
	{
		if ((*free_nodes))
			cleanup_and_exit(free_nodes, 1);
		else
		{
			ft_putstr_fd("malloc failed!\n", 2, 0);
			exit(1);
		}
	}
	my_env->env_strs = extract_strs_env(env, free_nodes);
	my_env->env_ll = extract_ll_env(my_env->env_strs, free_nodes);
	my_env->default_path = ft_split_leaks(PATH_H, "");
	return (my_env);
}

void	vals_init(t_vals *vals, char *line, t_free **f_nds)
{
	vals->nodes_num = 1 + count_pipes(line);
	vals->fix_spaces = add_spaces(line, f_nds);
	vals->before_str = ft_split_normal(vals->fix_spaces, " \t\n\v\f\r", f_nds);
	vals->str = ft_split_not_normal(vals->fix_spaces, " \t\n\v\f\r", f_nds);
	vals->i = 0;
	vals->j = vals->nodes_num;
	vals->len_line = 0;
	vals->len_before = 0;
}

void	append_new_node(t_exec **head, t_exec **current, t_free **free_nodes)
{
	t_exec	*new_node;

	new_node = create_new_node(free_nodes);
	if (!(*head))
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

int	ft_exit_status(int status, int flag)
{
	static int	stored_status;

	if (flag)
		stored_status = status;
	return (stored_status);
}
