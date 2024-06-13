/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:32:18 by eel-alao          #+#    #+#             */
/*   Updated: 2024/06/13 20:21:38 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	check_error(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3)
	{
		ft_putstr_fd("Usage: ./client [PID] [MESSAGE]\n", 2);
		exit(1);
	}
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]) && av[1][i] != '-')
		{
			ft_putstr_fd("PID must be a number\n", 2);
			exit(1);
		}
		i++;
	}
	if (*av[1] == '\0')
	{
		ft_putstr_fd("PID cannot be empty\n", 2);
		exit(1);
	}
	return (0);
}

void	send_char(char c, int pid)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			bit = kill(pid, SIGUSR1);
		else
			bit = kill(pid, SIGUSR2);
		if (bit == -1)
		{
			ft_putstr_fd("Error sending signal\n", 2);
			exit(1);
		}
		usleep(450);
		i--;
	}
}

void	send_msg(char *msg, int pid)
{
	int	i;

	i = 0;
	while (msg[i])
		send_char(msg[i++], pid);
	send_char('\0', pid);
}

int	main(int ac, char **av)
{
	int	pid;

	check_error(ac, av);
	pid = ft_atoi(av[1]);
	if (pid > MAX_PID)
	{
		ft_putstr_fd("PID is too high\n", 2);
		exit(1);
	}
	send_msg(av[2], pid);
	return (0);
}
