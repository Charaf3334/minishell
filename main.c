/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/25 15:06:57 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	if (g_sig == 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(130, 1);
	}
}

static void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

static void	shell_loop(t_env **my_env, t_free **free_nodes)
{
	char	*line;

	line = NULL;
	while (1)
	{
		(setup_signals(), env_and_1byte_alloc(my_env, free_nodes));
		g_sig = 1;
		line = readline("minishell>$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1, 0);
			if (free_nodes)
				ft_lstclear(free_nodes);
			close_all_fds();
			break ;
		}
		g_sig = 0;
		if (line[0])
			add_history(line);
		if (process_line(&line, free_nodes))
			continue ;
		process_execution(line, free_nodes, my_env);
		ft_lstclear(free_nodes);
		*free_nodes = NULL;
	}
}

int	main(int ac, char **av, char **env)
{
	t_free	*free_nodes;
	t_env	*my_env;

	free_nodes = NULL;
	(void)av;
	if (!isatty(1) || !isatty(0))
		return (1);
	if (ac == 1)
	{
		my_env = env_generator(env, &free_nodes);
		free_nodes->my_env = &my_env;
		shell_loop(&my_env, &free_nodes);
		free_env(&my_env);
	}
	rl_clear_history();
	return (ft_exit_status(0, 0));
}
