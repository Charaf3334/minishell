/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:39:44 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:26 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init1(t_cd *vars, char *pwd, char *new_path, t_free **free_nodes)
{
	int	i;

	i = 0;
	vars->parts = ft_split(vars->path, "/", free_nodes);
	vars->cap = ft_strlen(pwd) + ft_strlen(new_path) + 3;
	vars->stk = ft_malloc(sizeof *(vars->stk) * (vars->cap), free_nodes);
	vars->top = 0;
	while (vars->parts[i])
	{
		if (vars->parts[i][0] == '\0' || ft_strcmp(vars->parts[i], ".") == 0)
		{
			i++;
			continue ;
		}
		else if (ft_strcmp(vars->parts[i], "..") == 0)
		{
			if (vars->top > 0)
				vars->top--;
		}
		else
			vars->stk[vars->top++] = vars->parts[i];
		i++;
	}
}

void	helper_form_pwd(t_cd *vars, t_free **free_nodes)
{
	int	i;

	vars->total = 1;
	i = 0;
	while (i < vars->top)
		vars->total += ft_strlen(vars->stk[i++]) + 1;
	vars->res = ft_malloc(vars->total + 1, free_nodes);
	vars->p = vars->res;
	*(vars->p)++ = '/';
	i = 0;
	while (i < vars->top)
	{
		vars->len = ft_strlen(vars->stk[i]);
		ft_memcpy(vars->p, vars->stk[i], vars->len);
		vars->p += vars->len;
		if (i < vars->top - 1)
			*(vars->p)++ = '/';
		i++;
	}
}

char	*formated_pwd(char *pwd, char *new_path, t_free **free_nodes)
{
	t_cd	vars;

	if (new_path[0] == '/')
		vars.path = ft_strdup(new_path, free_nodes);
	else
	{
		vars.tmp = ft_strjoin(pwd, "/", free_nodes);
		vars.path = ft_strjoin(vars.tmp, new_path, free_nodes);
	}
	init1(&vars, pwd, new_path, free_nodes);
	if (vars.top == 0)
		return (ft_strdup("/", free_nodes));
	helper_form_pwd(&vars, free_nodes);
	*(vars.p) = '\0';
	return (vars.res);
}

void	cd_helper(t_exec *head, char *oldpwd_value, char *pwd,
		t_free **free_nodes)
{
	t_env_ll	*ll;
	t_env_ll	*new_ll;

	ll = (*head->my_env)->env_ll;
	while (ll)
	{
		if (!ft_strcmp(ll->key, "OLDPWD"))
		{
			free(ll->value);
			ll->value = ft_strdup_normal(oldpwd_value);
		}
		ll = ll->next;
	}
	free_and_delete_node(&(*head->my_env)->env_ll, "PWD", head);
	new_ll = ft_new_env_ll(ft_strjoin("PWD=", pwd, free_nodes), head);
	ft_lstadd_back(head->my_env, new_ll);
	refresh_env_strs(head);
}

int	cd_print_home_error(char *pwd, int flag, t_free **free_nodes)
{
	ft_putstr_fd(ft_strjoin("cd: HOME not set\n", NULL, free_nodes), 2, 0);
	if (flag)
		free(pwd);
	ft_exit_status(1, 1);
	return (1);
}
