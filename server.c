/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:40:03 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/01/18 20:17:20 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signal)
{
	static int				bits_counter = 0;
	static unsigned char	c = '\0';

	c <<= 1;
	if (signal == SIGUSR1)
		c |= 1;
	bits_counter++;
	if (bits_counter == 8)
	{
		write(1, &c, 1);
		bits_counter = 0;
		c = '\0';
	}
}

static void	print_server_pid(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	if (!server_pid)
		ft_putendl_fd("No Server PID", 2);
	else
	{
		ft_putstr_fd("Server PID :", 1);
		ft_putnbr_fd((int)server_pid, 1);
		write(1, "\n", 1);
	}
}

static void	init_sigaction(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		exit(EXIT_FAILURE);
}

int	main(void)
{
	print_server_pid();
	init_sigaction();
	while (1)
		pause();
	return (0);
}
