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

int error_node(t_philo *philo, t_list **lst)
{
    ft_putstr_fd("Error creating list\n", 2);
    free(philo);
    if (lst && *lst)
        (*lst)->next = NULL;
    ft_lstclear(lst, free);
    return (1);
}