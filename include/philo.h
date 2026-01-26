/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnieto-m <mnieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 11:13:18 by mario             #+#    #+#             */
/*   Updated: 2026/01/26 14:22:20 by mnieto-m         ###   ########.fr       */
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

# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define RESET		"\033[0m"
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
int	parsing(char **argv, int argc, t_data *data);
int	init_argv(char *argv[], int argc, t_data *data);
int	thread_control(t_data *data);
void	*checker_routine(void *arg);
void	*routine(void *arg);
t_philo	*get_next_philo(t_philo *philo);

void	cleanup_data(t_data *data);
int	error_node(t_philo *philo, t_list **lst);

void	speak(char *message, long start_time, t_philo *philo, long sleep_time);
long	get_time_in_milliseconds(void);
void	ft_usleep(long time, t_philo *philo);

#endif