/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-alao <eel-alao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:32:28 by eel-alao          #+#    #+#             */
/*   Updated: 2024/06/13 20:27:14 by eel-alao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, siginfo_t *info, void *m)
{
	static int				bit;
	static unsigned char	c;
	static int				pid;

	(void)m;
	if (pid != info->si_pid)
	{
		bit = 0;
		c = 0;
	}
	c |= ((signum == SIGUSR1));
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
	}
	else
		c <<= 1;
	pid = info->si_pid;
}

int	main(void)
{
	/**
	 * This function is the main server function for the Minitalk program.
	 * It sets up the server process by printing its PID, setting up signal handlers,
	 * and entering an infinite loop to wait for incoming signals.
	 *
	 * @return 0 on success, -1 on error
	 */
		int pid;
		struct sigaction signal;

		// Get the process ID of the server
		pid = getpid();

		// Print the server PID
		ft_putstr_fd("Server PID: ", 1);
		ft_putnbr_fd(pid, 1);
		ft_putchar_fd('\n', 1);

		// Set up the signal handler
		signal.sa_sigaction = sig_handler;
		signal.sa_flags = SA_SIGINFO;

		// Register the signal handler for SIGUSR1 and SIGUSR2
		if (sigaction(SIGUSR1, &signal, NULL) == -1)
			return (-1);
		if (sigaction(SIGUSR2, &signal, NULL) == -1)
			return (-1);

		// Enter an infinite loop to wait for incoming signals
		while (1)
			pause();

		return (0);
	
}
