/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:01:38 by mario             #+#    #+#             */
/*   Updated: 2026/01/25 20:10:51 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_philo_content(void *content)
{
	t_philo	*philo;

	if (!content)
		return ;
	philo = (t_philo *)content;
	pthread_mutex_destroy(&philo->fork);
	free(philo);
}

void	cleanup_data(t_data *data)
{
	t_list	*first;
	t_list	*current;

	if (!data)
		return ;
	if (data->philos)
	{
		first = data->philos;
		current = data->philos->next;
		while (current != first)
		{
			data->philos = current;
			current = current->next;
			free_philo_content(data->philos->content);
			free(data->philos);
		}
		free_philo_content(first->content);
		free(first);
		data->philos = NULL;
	}
	pthread_mutex_destroy(&data->shared);
}

int error_node(t_philo *philo, t_list **lst)
{
	ft_putstr_fd("Error creating list\n", 2);
	free(philo);
	if (lst && *lst)
		(*lst)->next = NULL;
	ft_lstclear(lst, free);
	return (1);
}