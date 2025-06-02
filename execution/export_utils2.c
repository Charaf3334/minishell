/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:49:59 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:49 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_no_value(t_exec *head, char *cmd)
{
	t_env_ll	*new_ll;

	if (find_key(cmd, (*head->my_env)->env_ll))
		return ;
	new_ll = ft_new_env_ll(cmd, head);
	ft_lstadd_back(head->my_env, new_ll);
	refresh_env_strs(head);
	ft_exit_status(0, 1);
}

void	export_normal_assign(t_exec *head, t_free **free_nodes, char *cmd)
{
	size_t		key_length;
	char		*temp_key;
	t_env_ll	*new_ll;

	key_length = ft_strchr(cmd, '=') - cmd;
	temp_key = ft_substr(cmd, 0, key_length, free_nodes);
	if (!ft_strcmp(temp_key, "_"))
	{
		ft_exit_status(0, 1);
		return ;
	}
	if (find_key(temp_key, (*head->my_env)->env_ll))
		free_and_delete_node(&((*head->my_env)->env_ll), temp_key, head);
	new_ll = ft_new_env_ll(cmd, head);
	ft_lstadd_back(head->my_env, new_ll);
	refresh_env_strs(head);
	ft_exit_status(0, 1);
}
