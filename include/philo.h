/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mario <mario@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:13:18 by mario             #+#    #+#             */
/*   Updated: 2026/01/23 00:12:01 by mario            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../Libft/include/libft.h"
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

struct s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				index;
	pthread_t		thread;
	pthread_mutex_t	fork;
	int				nbr_eats;
	long			last_meal;
}	t_philo;

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


int	init_struct(t_data *data);
int parsing(char **argv, int argc, t_data *data);
int control_philo(t_data *data);


int error_node(t_philo *philo, t_data *data);

#endif