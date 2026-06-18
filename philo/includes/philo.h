/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:09:27 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:10:43 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>

# define INVALID_ARGC 1
# define INVALID_ARGV 2

typedef struct s_global
{
	int				number_of_philosphers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_must_eat;
	int				is_dead;
	int				have_eaten_enough;
	long			start_simulation;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_is_dead;
	pthread_mutex_t	lock_time_last_meal;
	pthread_mutex_t	lock_number_of_meals_eaten;
	pthread_mutex_t	lock_have_eaten_enough;
} t_global;

typedef struct s_philo
{
	int				id;
	long			time_last_meal;
	int				number_of_meals_eaten;
	pthread_t		philo;
	t_global		*global;
	struct s_philo		*philos;
} t_philo;

// Functions called by main
int		log_start_time(t_global *global);
int		validate_args(int argc, char **argv);
int		setup(char **argv, t_philo **philo, t_global **global);
int		launch(t_philo *philo);
int		clean_setup(t_philo *philo);

// Exit program conditions
int	is_dead_routine(t_philo *philo);
int	monitor_death(t_philo *philo);
int	monitor_eating(t_philo *philo);
int	have_eaten_enough_routine(t_philo *philo);

// Utils
long	log_timestamp(t_global *global);
int		error(char *msg, int to_ret);
void	convert_to_int(char **argv, t_global **global);

// Elements of routine
int	grab_right_fork(t_philo *philo);
int	grab_left_fork(t_philo *philo);
int	release_right_fork(t_philo *philo);
int	release_left_fork(t_philo *philo);
int	eat(t_philo *philo);
int	ft_sleep(t_philo *philo);
int	ft_think(t_philo *philo);

#endif