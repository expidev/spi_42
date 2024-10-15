/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nharivon <nharivon@42student.antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:21:37 by nharivon          #+#    #+#             */
/*   Updated: 2024/09/10 08:21:39 by nharivon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h> 
#include <unistd.h>

int	g_signal_sent = 0;

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while ((*nptr >= 9 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	if (*nptr != '\0')
		return (0);
	return (res * sign);
}

void	confirm_received_signal(int signum)
{
	g_signal_sent = 1;
	(void) signum;
}

void	send_bits(pid_t pid, unsigned char c)
{
	int	i;
	
	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		
		while (!g_signal_sent)
			usleep(100);
		g_signal_sent = 0;
	}
}

int	main(int nb, char **argv)
{
	pid_t			pid;
	struct sigaction	act;
	int			i;
	
	pid = ft_atoi(argv[1]);
	act.sa_handler = &confirm_received_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	i = 0;
	if (nb != 3 || pid <= 0)
		return (1);
	
	sigaction(SIGUSR2, &act, NULL);
	
	while (argv[2][i] != '\0')
	{
		send_bits(pid, argv[2][i]);
		i++;
	}
	
	while (1)
		sleep(42);
	return (0);
}



