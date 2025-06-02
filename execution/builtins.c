/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:37:40 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:24 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	builtin_env(t_exec *head, t_free **free_nodes)
{
	int	i;

	if (head->len_cmds > 1)
	{
		print_error(head->cmd[1], 2, free_nodes);
	}
	else
	{
		i = 0;
		while ((*head->my_env)->env_strs[i])
		{
			if (ft_strchr((*head->my_env)->env_strs[i], '='))
				printf("%s\n", (*head->my_env)->env_strs[i]);
			i++;
		}
	}
	return (1);
}

static void	echo_helper(int i, t_exec *head)
{
	while (head->cmd[i])
	{
		write(1, head->cmd[i], ft_strlen(head->cmd[i]));
		if (++i == head->len_cmds)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
}

static int	builtin_echo(t_exec *head)
{
	int	i;
	int	opt;

	opt = echo_option(head);
	if (head->len_cmds > 1 && opt > 0)
	{
		i = opt;
		while (head->cmd[i])
		{
			ft_putstr_fd(head->cmd[i], 1, 0);
			if (head->cmd[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	else if (head->len_cmds == 1)
		write(1, "\n", 1);
	else
		echo_helper(-opt, head);
	return (1);
}

static int	builtin_pwd(t_exec *head, t_free **free_nodes)
{
	t_quotes	c;
	char		*pwd;
	int			flag;

	c.free_nodes = free_nodes;
	c.node = head;
	flag = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		flag = 1;
		pwd = my_getenv(&c, "PWD");
	}
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	if (!flag)
		free(pwd);
	return (1);
}

int	handle_builtins(t_exec *head, t_free **free_nodes)
{
	if (head->cmd[0] && !ft_strcmp(head->cmd[0], "env"))
		return (builtin_env(head, free_nodes));
	if (head->cmd[0] && !ft_strcmp(head->cmd[0], "echo"))
		return (builtin_echo(head));
	if (head->cmd[0] && !ft_strcmp(head->cmd[0], "pwd"))
		return (builtin_pwd(head, free_nodes));
	return (0);
}
