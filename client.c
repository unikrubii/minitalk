/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:22:35 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/27 13:45:18 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_client;

char	*itoa_bit(int n)
{
	char	*ret;
	int				i;
	int				base;

	if (n < 0)
		n += 256;
	ret = (char *)malloc(sizeof(char) * (8 + 1));
	i = 0;
	base = 128;
	while (i < 8)
	{
		ret[i] = (n / base) + '0';
		i++;
		n %= base;
		base /= 2;
	}
	ret[i] = '\0';
	return (ret);
}

void	sig_send(char *bit)
{
	int	i;

	i = 0;
	while (bit[i])
	{
		if (bit[i] == '0')
		{
			if (kill(g_client.pid, SIGUSR1) > 0)
				write(1, "Error occurs on sending signal!\n", 32);
			// else
				// write(1, "0", 1);
		}
		else if (bit[i] == '1')
		{
			if (kill(g_client.pid, SIGUSR2) > 0)
				write(1, "Error occurs on sending signal!\n", 32);
			// else
				// write(1, "1", 1);
		}
		i++;
		usleep(100);
	}
}

void c_handler(int signum, siginfo_t *sa, void *old)
{
	static int	pid = 0;

	(void)old;
	(void)sa;
	if (signum == SIGUSR1)
	{
		// write(1, "Letter received!\n", 17);
	}
	else if (signum == SIGUSR2)
		write(1, "Sending finished!\n", 18);
}

void	init_client(char *pid, struct sigaction *sa)
{
	int	i;
	int	num;

	sa->sa_sigaction = c_handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	i = 0;
	num = 0;
	while (pid[i] >= '0' && pid[i] <= '9')
	{
		num = (num * 10) + (pid[i] - '0');
		i++;
	}
	g_client.pid = num;
}

int	main(int ac, char **av)
{
	pid_t				s_pid;
	struct sigaction	sa;
	int					i;
	char				*bit;
	
	if (ac != 3)
		exit(-1);
	init_client(av[1], &sa);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (*av[2])
	{
		bit = itoa_bit(*av[2]);
		sig_send(bit);
		free(bit);
		av[2]++;
		usleep(100);
	}
	i = 0;
	while (i++ < 8)
	{
		kill(g_client.pid, SIGUSR1);
		usleep(10);
	}
}
