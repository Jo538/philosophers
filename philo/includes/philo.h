/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:09:27 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 14:48:46 by jchartie         ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				number_of_philosphers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_last_meal;
	int				number_of_times_must_eat;
	int				number_of_meals_eaten;
	pthread_t		philo;
	pthread_t		monitor;
	pthread_mutex_t	lock;
	pthread_mutex_t	lock2;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	long			start_simulation;	
} t_philo;


int	validate_args(int argc, char **argv);
void	convert_to_int(char **argv, t_philo *philo);
int	initialise_setup(char **argv, t_philo *philo);
int	make_philo_and_call_routine(t_philo *philo);
int	clean_setup(t_philo *philo);
int	log_start_time(t_philo *philo);
long	log_timestamp(t_philo *philo);

// Elements of routine
int	launch(t_philo *philo);
int	grab_right_fork(t_philo *philo);
int	grab_left_fork(t_philo *philo);
int	release_right_fork(t_philo *philo);
int	release_left_fork(t_philo *philo);
int	eat(t_philo *philo);
int	philo_sleep_and_think(t_philo *philo);

#endif