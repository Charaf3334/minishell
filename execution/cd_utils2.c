/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:09:26 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/01 16:27:30 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_no_args_helper(char *home, t_quotes *c, int flag, char *pwd)
{
	if (access(home, F_OK) != 0)
	{
		print_error(home, 2, c->free_nodes);
		ft_exit_status(1, 1);
		if (flag)
			free(pwd);
	}
}

int	cd_no_args(t_quotes *c, t_exec *head, char *pwd, int flag)
{
	char	*home;

	home = my_getenv(c, "HOME");
	if (!home)
		return (cd_print_home_error(pwd, flag, c->free_nodes));
	if (head->nodes_num == 1)
	{
		if (chdir(home) == -1)
		{
			perror(home);
			ft_exit_status(1, 1);
			if (flag)
				free(pwd);
			return (1);
		}
		cd_helper(head, pwd, home, c->free_nodes);
	}
	else
		return (cd_no_args_helper(home, c, flag, pwd), 1);
	ft_exit_status(0, 1);
	if (flag)
		free(pwd);
	return (1);
}

int	cd_handle_file(char *path, t_free **free_nodes)
{
	print_error(path, 7, free_nodes);
	ft_exit_status(1, 1);
	return (1);
}
