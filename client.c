/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:25:22 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/01/18 20:45:29 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal_bits(char character, pid_t pid_server)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if ((character >> bits & 1) == 1)
		{
			if (kill(pid_server, SIGUSR1) == ERROR)
			{
				ft_putendl_fd("Error | Kill Fails", 2);
				break ;
			}
		}
		else
		{
			if (kill(pid_server, SIGUSR2) == ERROR)
			{
				ft_putendl_fd("Error | Kill Fails", 2);
				break ;
			}
		}
		--bits;
		usleep(350);
	}
}

static int	is_valid_arg(char *pid, char *msg)
{
	int	r;
	int	i;

	r = 1;
	i = -1;
	if (msg[0] == '\0')
		r = 0;
	while (r == 1 && pid[++i])
	{
		if (!(pid[i] >= '0' && pid[i] <= '9'))
			r = 0;
	}
	return (r);
}

int	main(int argc, char **argv)
{
	int	j;

	j = -1;
	if (argc == 3 && is_valid_arg(argv[1], argv[2]))
	{
		while (argv[2][++j])
			send_signal_bits(argv[2][j], ft_atoi(argv[1]));
	}
	else
		ft_putendl_fd("Error | Correct: ./client <PID> Message\n", 2);
	return (0);
}
