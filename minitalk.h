/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:08:06 by sthitiku          #+#    #+#             */
/*   Updated: 2022/05/27 13:34:06 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_server
{
	int		count;
	char	c;
	pid_t	c_pid;
}	t_server;

typedef struct s_client
{
	int		count;
	pid_t	pid;
}	t_client;

#endif