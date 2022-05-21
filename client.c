/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:22:35 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/22 02:18:03 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_client	g_client;

char	*itoa_bit(int n)
{
	char	*ret;
	int		i;
	int		base;

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

int	mt_atoi(char *pid)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (pid[i] >= '0' && pid[i] <= '9')
	{
		num = (num * 10) + (pid[i] - '0');
		i++;
	}
	return (num);
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
			else
				write(1, "0\n", 1);
		}
		else if (bit[i] == '1')
		{
			if (kill(g_client.pid, SIGUSR2) > 0)
				write(1, "Error occurs on sending signal!\n", 32);
			else
				write(1, "1\n", 1);
		}
		i++;
		usleep(200);
	}
}

void	conv_input(char *str)
{
	int		i;
	char	*bit;

	i = 0;
	while (str[i])
	{
		bit = itoa_bit(str[i]);
		sig_send(bit);
		free(bit);
		i++;
		usleep(200);
	}
}

void c_handler(int signum, siginfo_t *sa, void *old)
{
	static int	pid = 0;

	(void)old;
	(void)sa;
	if (signum == SIGUSR1)
	{
		write(1, "SIGUSR1 Recieved!\n", 18);
	}
	else if (signum == SIGUSR2)
	{
		write(1, "SIGUSR2 Recieved!\n", 18);
	}
}

int	main(int ac, char **av)
{
	pid_t	s_pid;
	struct sigaction	sa;
	
	if (ac != 3)
		exit(-1);
	g_client.pid = mt_atoi(av[1]);
	sa.sa_sigaction = c_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	conv_input(av[2]);
	// kill(s_pid, SIGUSR1);
}