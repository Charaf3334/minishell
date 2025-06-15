/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:31:40 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/14 12:56:33 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_nodes_helper(int p_fd[], int nodes_nums, t_exec *node,
		t_free **free_nodes)
{
	close(p_fd[1]);
	if (nodes_nums > 1)
		ft_dup2(p_fd[0], STDIN_FILENO, node->my_env, free_nodes);
	if (node->heredoc_fd != -1)
		close(node->heredoc_fd);
	close(p_fd[0]);
}

void	append_node(t_env_ll **env_ll, char *key, char *value,
	t_free **free_nodes)
{
	t_env_ll	*current;
	char		*new_value;

	if (!env_ll || !*env_ll)
		return ;
	current = *env_ll;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			new_value = ft_strjoin_normal(current->value, value, free_nodes);
			if (current->value)
				free(current->value);
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
}

void	ft_remove_path(char *key, t_exec *head)
{
	if (!ft_strcmp(key, "PATH"))
	{
		free((*head->my_env)->default_path[0]);
		(*head->my_env)->default_path[0] = NULL;
		return ;
	}
}

void	free_and_delete_node(t_env_ll **env_ll, char *key, t_exec *head)
{
	t_env_ll	*current;
	t_env_ll	*previous;

	if (!env_ll || !*env_ll)
		return ;
	current = *env_ll;
	previous = NULL;
	ft_remove_path(key, head);
	while (current)
	{
		if (!ft_strcmp(current->key, key) && ft_strcmp(current->key, "_"))
		{
			if (previous)
				previous->next = current->next;
			else
				*env_ll = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	find_key(char *key, t_env_ll *env_ll)
{
	t_env_ll	*tmp;

	tmp = env_ll;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
