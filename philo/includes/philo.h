/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:09:27 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 22:26:52 by admin            ###   ########.fr       */
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
	long			time_last_meal;
	int				number_of_meals_eaten;
	pthread_t		philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;	
} t_philo;

typedef struct s_global
{
	int				number_of_philosphers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_must_eat;
	long			start_simulation;
	pthread_t		monitor;
	pthread_mutex_t	lock;
	pthread_mutex_t	lock2;
} t_global;

typedef struct s_param
{
	t_global	global;
	t_philo		philo;
} t_param;

// Functions called by main
int		log_start_time(t_global *global);
int		validate_args(int argc, char **argv);
int		initialise_setup(char **argv, t_param *param);
int		launch(t_param *param);
int		clean_setup(t_param *param);

// Exit program conditions
int	is_dead(t_param *param);
int	has_eaten_enough(t_param *param);

// Utils
long	log_timestamp(t_global *global);
int		error(char *msg, int to_ret);
void	convert_to_int(char **argv, t_global *global);

// Elements of routine
int	grab_right_fork(t_param *param);
int	grab_left_fork(t_param *param);
int	release_right_fork(t_philo *philo);
int	release_left_fork(t_philo *philo);
int	eat(t_param *param);
int	ft_sleep(t_param *param);

#endif