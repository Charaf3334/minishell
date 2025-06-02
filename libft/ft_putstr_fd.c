/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:07:15 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:15 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *str, int fd, int option)
{
	size_t	len;

	len = ft_strlen(str);
	write(fd, str, len);
	if (option == 1)
		write(fd, "\n", 1);
}
