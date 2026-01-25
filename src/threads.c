/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 01:30:53 by mario             #+#    #+#             */
/*   Updated: 2026/01/23 21:34:18 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	threads_manage(t_data *data)
{
	if (data->nbr_must_eat != 0)
	{
		if (init_mtx(data))
			return (1);
		if (create_n_join_philos(data))
			return (1);
		if (pthread_join(data->checker, NULL))
			ft_putstr_fd("Error at joining thread\n", 2);
		destroy_mtx(data, data->nbr_philos);
	}
	ft_lstclear(&data->philos);
	return (0);
}
