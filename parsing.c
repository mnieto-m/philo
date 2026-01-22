/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:43:23 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 12:32:54 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int init_argv(char *argv[], int argc, t_data *data)
{
	int flag;

	flag  = 0;
	data->nbr_philos = ft_atoi_flag(argv[1],(flag) * 0);
	if(flag == -1)
		return(1);
	data->t_die = ft_atoi_flag(argv[2],&flag);
	if(flag == -1)
		return(1);
	data->t_eat = ft_atoi_flag(argv[3],&flag);
	if(flag == -1)
		return(1);
	data->t_sleep = ft_atoi_flag(argv[4],&flag);
	if(flag == -1)
		return(1);
	if(argc == 6)
	{
		data->nbr_philos = ft_atoi_flag(argv[1],&flag);
		if(flag == -1)
			return(1);
	}
	else
		data->nbr_must_eat = -1;
	return(0);	
}

int parsing(char **argv, int argc, t_data *data)
{
	int i;
	int j;

	i = 1;
	while(argv[i])
	{

		j = 0;
		while(argv[i][j])
		{
			
			if(!ft_isdigit(argv[i][j]))
				return(ft_putstr_fd("numbers without sings\n",2),1);
			j++;
		}
		i++;
	}
	if(init_argv(argv, argc, data));
		return(1);
	return(0);
}