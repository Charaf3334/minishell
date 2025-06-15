/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:40:55 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:39:49 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**gen_strs_env(t_env_ll *env_ll, t_free **f_nds)
{
	char		**strs;
	t_env_ll	*head;
	int			i;
	int			len;

	1 && (head = env_ll, len = 0);
	while (head)
		1 && (len++, head = head->next);
	strs = malloc((len + 1) * sizeof(char *));
	if (!strs)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(f_nds, 1);
	}
	1 && (i = 0, head = env_ll);
	while (head)
	{
		if (head->value)
			strs[i] = ft_strjoin3_normal(head->key, "=", head->value, f_nds);
		else
			strs[i] = ft_strdup_normal(head->key, f_nds);
		1 && (i++, head = head->next);
	}
	strs[len] = NULL;
	return (strs);
}

void	refresh_env_strs(t_exec *head, t_free **free_nodes)
{
	char	**old;
	int		j;

	old = (*head->my_env)->env_strs;
	j = 0;
	while (old[j])
		free(old[j++]);
	free(old);
	(*head->my_env)->env_strs = gen_strs_env((*head->my_env)->env_ll,
			free_nodes);
}

void	print_export_env(char **env_quotes, int out_fd, t_free **free_nodes)
{
	char	*line;
	int		i;

	i = 0;
	while (env_quotes[i])
	{
		if (env_quotes[i][0] == '_' && env_quotes[i][1] == '=')
		{
			i++;
			continue ;
		}
		line = ft_strjoin3("declare -x ", env_quotes[i], "\n", free_nodes);
		write(out_fd, line, ft_strlen(env_quotes[i]) + 12);
		i++;
	}
}

void	handle_export_no_args(t_exec *head, t_free **free_nodes, int *p_fd,
		int nodes_nums)
{
	char	**env_quotes;

	env_quotes = format_env_vars((*head->my_env)->env_strs, free_nodes);
	if (nodes_nums > 1 && head->len_outfiles == 0)
	{
		print_export_env(env_quotes, p_fd[1], free_nodes);
		close(p_fd[1]);
		ft_dup2(p_fd[0], STDIN_FILENO, head->my_env, free_nodes);
	}
	else
	{
		if (head->len_outfiles > 0)
		{
			close(p_fd[1]);
			close(p_fd[0]);
			open_outfile(head, free_nodes);
		}
		print_export_env(env_quotes, 1, free_nodes);
		if (nodes_nums == 1)
		{
			close(p_fd[1]);
			close(p_fd[0]);
		}
	}
	ft_exit_status(0, 1);
}

void	export_append_value(t_exec *head, t_free **free_nodes, char *cmd)
{
	size_t		key_length;
	char		*temp_key;
	char		*temp_value;
	t_env_ll	*new_ll;

	key_length = ft_strchr(cmd, '+') - cmd;
	temp_key = ft_substr(cmd, 0, key_length, free_nodes);
	temp_value = ft_substr(cmd, ft_strchr(cmd, '=') - cmd + 1, ft_strlen(cmd)
			- (ft_strchr(cmd, '=') - cmd + 1), free_nodes);
	if (!ft_strcmp(temp_key, "_"))
	{
		ft_exit_status(0, 1);
		return ;
	}
	if (find_key(temp_key, (*head->my_env)->env_ll))
		append_node(&((*head->my_env)->env_ll), temp_key, temp_value,
			free_nodes);
	else
	{
		new_ll = ft_new_env_ll_2(temp_key, temp_value, head, free_nodes);
		ft_lstadd_back(head->my_env, new_ll);
	}
	refresh_env_strs(head, free_nodes);
	ft_exit_status(0, 1);
}
