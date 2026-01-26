/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 01:30:53 by mario             #+#    #+#             */
/*   Updated: 2026/01/26 13:56:37 by mnieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*get_next_philo(t_philo *philo)
{
	t_list	*current;

	current = philo->data->philos;
	while (current)
	{
		if (((t_philo *)current->content) == philo)
			return ((t_philo *)current->next->content);
		current = current->next;
	}
	return (NULL);
}
static void	create_checker(t_data *data)
{
	if (pthread_create(&data->checker, NULL, &checker_routine, data->philos))
	{
		ft_putstr_fd("Error at creating thread\n", 2);
		ft_lstclear(&data->philos, NULL);
	}
}

static int	create_n_join_philos(t_data *data)
{
	data->start_time = get_time_in_milliseconds();
	if (data->start_time == -1)
		return (1);
	while (((t_philo *)data->philos->content)->index <= data->nbr_philos)
	{
		if (pthread_create(&((t_philo *)data->philos->content)->thread, NULL, &routine, data->philos->content))
			ft_putstr_fd("Error at creating thread\n", 2);
		if (((t_philo *)data->philos->content)->index == data->nbr_philos)
			break ;
		data->philos = data->philos->next;
	}
	data->philos = data->philos->next;
	create_checker(data);
	while (((t_philo *)data->philos->content)->index <= data->nbr_philos)
	{
		if (pthread_join(((t_philo *)data->philos->content)->thread, NULL))
			ft_putstr_fd("Error at joining thread\n", 2);
		if (((t_philo *)data->philos->content)->index == data->nbr_philos)
			break ;
		data->philos = data->philos->next;
	}
	data->philos = data->philos->next;
	return (0);
}

static int	init_mutex(t_data **data)
{
	while (((t_philo *)(*data)->philos->content)->index <= (*data)->nbr_philos)
	{
		if (pthread_mutex_init(&((t_philo *)(*data)->philos->content)->fork, NULL))
		{
			ft_putstr_fd("Error at initializing mutex\n", 2);
			cleanup_data(*data);
			return (1);
		}
		if (((t_philo *)(*data)->philos->content)->index == (*data)->nbr_philos)
			break ;
		(*data)->philos = (*data)->philos->next;
	}
	(*data)->philos = (*data)->philos->next;
	if (pthread_mutex_init(&(*data)->shared, NULL))
	{
		ft_putstr_fd("Error at initializing mutex\n", 2);
		cleanup_data(*data);
		return (1);
	}
	return (0);
}

int	thread_control(t_data *data)
{
	if (data->nbr_must_eat != 0)
	{
		if (init_mutex(&data))
			return (1);
		if (create_n_join_philos(data))
			return (1);
		if (pthread_join(data->checker, NULL))
			ft_putstr_fd("Error at joining thread\n", 2);
	}
	cleanup_data(data);
	return (0);
}
