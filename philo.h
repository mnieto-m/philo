/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:13:18 by mario             #+#    #+#             */
/*   Updated: 2026/01/22 11:31:04 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

#define ERROR_PARSING "ARG DEFINE: nbr_of_philos, time_to_die, time_to_eat,\
 time_to_sleep, optional[nbr_of_times_each_philo_must_eat]"

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DIE	"died"

typedef struct s_philo
{
	int index;
	ptheread_t index;
	pthread_mutex fork;
	int	 nbr_eats;
	long last_meals;
}t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_must_eat;
	long			start_time;
	pthread_t		checker;
	t_list			*philos;
	pthread_mutex_t	shared;
	int				exit_flag;
}	t_data;

#endif