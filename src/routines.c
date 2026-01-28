/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 01:33:11 by mario             #+#    #+#             */
/*   Updated: 2026/01/28 16:42:59 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


static int	take_forks(t_philo *philo)
{
	t_philo	*next_philo;

	next_philo = get_next_philo(philo);
	if(philo->index % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		speak(FORK, philo->data->start_time, philo, 0);
		pthread_mutex_lock(&next_philo->fork);
		speak(FORK, philo->data->start_time, philo, 0);
	}
	else
	{
		pthread_mutex_lock(&next_philo->fork);
		speak(FORK, philo->data->start_time, philo, 0);
		if (philo->data->nbr_philos == 1)
		{
			pthread_mutex_unlock(&next_philo->fork);
			return (1);
		}
		pthread_mutex_lock(&philo->fork);
		speak(FORK, philo->data->start_time, philo, 0);
	}
	return (0);
}

static int	eat(t_philo *philo)
{
	t_philo	*next_philo;

	if (take_forks(philo))
		return (1);
	next_philo = get_next_philo(philo);
	pthread_mutex_lock(&philo->data->shared);
	philo->last_meal = get_time_in_milliseconds();
	philo->nbr_eats++;
	pthread_mutex_unlock(&philo->data->shared);
	speak(EAT, philo->data->start_time, philo, philo->data->t_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&next_philo->fork);
	pthread_mutex_lock(&philo->data->shared);
	if (philo->nbr_eats == philo->data->nbr_must_eat)
	{
		pthread_mutex_unlock(&philo->data->shared);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->shared);
	return (0);
}

static int	check_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->shared);
	if (philo->data->exit_flag)
	{
		pthread_mutex_unlock(&philo->data->shared);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->shared);
	return (0);
}

static long	t_think(t_philo *philo)
{
	long	think_time;

	think_time = (philo->data->t_eat * 2) - philo->data->t_sleep;
	if (think_time < 0)
		think_time = 0;
	return (think_time);
}


void	*routine(void *arg)
{
	t_philo		*philo;
	long		think_time;

	philo = (t_philo *)arg;
	think_time = t_think(philo);
	if (philo->index % 2 == 1 && philo->data->nbr_philos != 1)
		ft_usleep(50, philo);
	while (!check_exit(philo))
	{
		if (eat(philo))
			break ;
		speak(SLEEP, philo->data->start_time, philo, philo->data->t_sleep);
		if (philo->data->nbr_philos % 2 == 1)
		{
			if (philo->index % 2 == 1)
				speak(THINK, philo->data->start_time, philo, think_time * 0.42);
			else
				speak(THINK, philo->data->start_time, philo, 0);
		}
		else
			speak(THINK, philo->data->start_time, philo, 0);
	}
	return (arg);
}
