/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:36:34 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 12:36:02 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(char **argv, int argc)
{
	t_data data;
	
	if(argc !=  5 && argc != 6)
		return(ft_putstr(ERROR_PARSING"\n",2));
	memset(&data,0, sizeof(t_data));
	if(!parsing(argv, argc , &data));
		return(1);
	if(init_struc(&data));
		return(1);
	if(control_philo(&data))
		return(1);
	return(0);
}