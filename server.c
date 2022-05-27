/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:22:33 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/27 13:19:48 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	g_server;

void	put_nbr(int nb)
{
	char	c;
	
	if (nb >= 10)
		put_nbr(nb / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void	add_zero(pid_t c_pid)
{
	g_server.c += 0;
	g_server.count++;
	if (g_server.count < 8)
		g_server.c <<= 1;
	else
	{
		if (g_server.c == 0)
			kill(c_pid, SIGUSR2);
		else
		{
			write(1, &g_server.c, 1);
			g_server.c = 0;
			g_server.count = 0;
			kill(c_pid, SIGUSR1);
		}
	}
}

void	add_one(pid_t c_pid)
{
	g_server.c += 1;
	g_server.count++;
	if (g_server.count < 8)
		g_server.c <<= 1;
	else
	{
		if (g_server.c == '\0')
			kill(c_pid, SIGUSR2);
		else
		{
			write(1, &g_server.c, 1);
			g_server.c = 0;
			g_server.count = 0;
			kill(c_pid, SIGUSR1);
		}
	}
}

void	s_handler(int signum, siginfo_t *sa, void *old)
{
	(void)old;
	if (!g_server.c_pid)
	{
		g_server.c_pid = sa->si_pid;
	}
	if (signum == SIGUSR1)
	{
		add_zero(g_server.c_pid);
	}
	else if (signum == SIGUSR2)
	{
		add_one(g_server.c_pid);
	}
}

int	main(void)
{
	struct sigaction	sa;

	write(1, "pid = ", 6);
	put_nbr(getpid());
	write(1, "\n", 1);
	g_server.c = 0;
	g_server.count = 0;
	sa.sa_sigaction = s_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		usleep(10);
	}
}