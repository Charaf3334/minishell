/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:35:15 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:40 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_ll	*ft_new_env_ll_2(char *key, char *value, t_exec *head)
{
	t_env_ll	*new_env;

	new_env = create_new_env();
	new_env->key = ft_strdup_normal(key);
	if (!ft_strcmp(key, "PATH"))
		new_env->value = ft_strjoin_normal((*head->my_env)->default_path[0],
				value);
	else
		new_env->value = ft_strjoin_normal(value, "");
	return (new_env);
}

t_env_ll	*ft_new_env_ll(char *str, t_exec *node)
{
	t_env_ll	*new_env;
	char		*equal_sign;
	int			key_length;

	new_env = create_new_env();
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
	{
		new_env->key = ft_strdup_normal(str);
		if (!ft_strcmp(str, "PATH"))
			new_env->value = ft_strdup_normal((*node->my_env)->default_path[0]);
		else
			new_env->value = NULL;
	}
	else
	{
		key_length = equal_sign - str;
		new_env->key = ft_substr_normal(str, 0, key_length);
		new_env->value = ft_strdup_normal(equal_sign + 1);
	}
	return (new_env);
}

int	wait_for_childs(int *quit_printed, t_exec *head)
{
	int		status;
	int		sig;
	int		print_newline;

	print_newline = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
				print_newline = 1;
			else if (sig == SIGQUIT && !(*quit_printed))
			{
				if (head->nodes_num == 1)
					write(1, "Quit (core dumped)\n", 19);
				*quit_printed = 1;
			}
		}
	}
	return (print_newline);
}
