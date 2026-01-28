/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 01:34:20 by mario             #+#    #+#             */
/*   Updated: 2026/01/29 00:36:18 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time_in_milliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long wait, t_philo *philo)
{
	long	start_time;

	start_time = get_time_in_milliseconds();
	while (1)
	{
		if (get_time_in_milliseconds() >= start_time + wait)
			break ;
		pthread_mutex_lock(&philo->data->shared);
		if (philo->data->exit_flag)
		{
			pthread_mutex_unlock(&philo->data->shared);
			break ;
		}
		pthread_mutex_unlock(&philo->data->shared);
	}
}

void	speak(char *msg, long start_time, t_philo *philo, long wait_time)
{
	pthread_mutex_lock(&philo->data->shared);
	if (philo->data->exit_flag)
	{
		pthread_mutex_unlock(&philo->data->shared);
		if (!ft_strncmp(msg, DIE, 4))
			printf(RED "%ld %d %s\n" RESET, get_time_in_milliseconds()
				- start_time, philo->index, msg);
		return ;
	}
	if (!ft_strncmp(msg, FORK, 16))
		printf(MAGENTA "%ld %d %s\n" RESET, get_time_in_milliseconds()
			- start_time, philo->index, msg);
	else if (!ft_strncmp(msg, EAT, 9))
		printf(GREEN "%ld %d %s\n" RESET, get_time_in_milliseconds()
			- start_time, philo->index, msg);
	else if (!ft_strncmp(msg, SLEEP, 11))
		printf(BLUE "%ld %d %s\n" RESET, get_time_in_milliseconds()
			- start_time, philo->index, msg);
	else if (!ft_strncmp(msg, THINK, 11))
		printf(YELLOW "%ld %d %s\n" RESET, get_time_in_milliseconds()
			- start_time, philo->index, msg);
	pthread_mutex_unlock(&philo->data->shared);
	ft_usleep(wait_time, philo);
}
