/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:41:13 by mnieto-m          #+#    #+#             */
/*   Updated: 2026/01/26 14:05:33 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	obtain_e_time(t_philo *philo, long *e_time)
{
	pthread_mutex_lock(&philo->data->shared);
	if (philo->nbr_eats == 0)
	{
		pthread_mutex_unlock(&philo->data->shared);
		*e_time = get_time_in_milliseconds() - philo->data->start_time;
	}
	else
	{
		*e_time = get_time_in_milliseconds() - philo->last_meal;
		pthread_mutex_unlock(&philo->data->shared);
	}
}

static int	check_must_eat(t_philo *philo)
{
	int		i;
	int		count;
	t_philo	*current;

	i = 0;
	count = 0;
	current = philo;
	pthread_mutex_lock(&philo->data->shared);
	while (i < philo->data->nbr_philos)
	{
		if (current->nbr_eats == philo->data->nbr_must_eat)
			count++;
		current = get_next_philo(current);
		i++;
	}
	pthread_mutex_unlock(&philo->data->shared);
	if (count == philo->data->nbr_philos)
		return (1);
	return (0);
}

void	*checker_routine(void *arg)
{
	t_philo		*philo;
	long		e_time;
	t_list		*first;

	first = (t_list *)arg;
	philo = (t_philo *)first->content;
	while (1)
	{
		obtain_e_time(philo, &e_time);
		if (e_time > philo->data->t_die)
		{
			pthread_mutex_lock(&philo->data->shared);
			philo->data->exit_flag = 1;
			if (philo->nbr_eats != philo->data->nbr_must_eat)
			{
				pthread_mutex_unlock(&philo->data->shared);
				speak(DIE, philo->data->start_time, philo, 0);
				pthread_mutex_lock(&philo->data->shared);
			}
			pthread_mutex_unlock(&philo->data->shared);
			break ;
		}
		if (check_must_eat(philo))
			break ;
		philo = get_next_philo(philo);
	}
	return (arg);
}
