/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:01:38 by mario             #+#    #+#             */
/*   Updated: 2026/01/23 00:07:38 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int error_node(t_philo *philo, t_data *data)
{
	ft_putstr_fd("Error creating list\n", 2);
	free(philo);
	clear_circular_list(&data->philos);
	return (1);
}