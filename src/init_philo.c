/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:37:43 by mario             #+#    #+#             */
/*   Updated: 2026/01/23 00:07:29 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_philo	*create_philo(int index, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->data = data;
	philo->index = index;
	philo->nbr_eats = 0;
	philo->last_meal = -1;
	return (philo);
}

static void	free_philo(void *content)
{
	if (content)
		free(content);
}

static void	clear_circular_list(t_list **lst)
{
	t_list	*tmp;
	t_list	*head;

	if (!lst || !(*lst))
		return ;
	head = *lst;
	(*lst)->next = NULL;
	ft_lstclear(lst, free_philo);
}

int	init_struct(t_data *data)
{
	int		i;
	t_list	*last;
	t_list	*new_node;
	t_philo	*philo;

	i = 0;
	while (++i <= data->nbr_philos)
	{
		philo = create_philo(i, data);
		if (!philo)
		{
			ft_putstr_fd("Error creating philo\n", 2);
			clear_circular_list(&data->philos);
			return (1);
		}
		new_node = ft_lstnew(philo);
		if (!new_node)
			error_node(philo, &data);
		ft_lstadd_back(&data->philos, new_node);
		if (i == data->nbr_philos)
			last = new_node;
	}
	last->next = data->philos;
	return (0);
}
