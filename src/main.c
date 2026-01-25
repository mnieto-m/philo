/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:36:34 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 23:28:28 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_data data;
	
	if(argc !=  5 && argc != 6)
		return(ft_putstr_fd(ERROR_PARSING"\n",2),1);
	memset(&data,0, sizeof(t_data));
	if(!parsing(argv, argc , &data))
		return(1);
	if(init_struct(&data))
		return(1);
	if(control_philo(&data))
		return(1);
	return(0);
}