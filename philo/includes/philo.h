/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:09:27 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 16:06:51 by admin            ###   ########.fr       */
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
	int	id;
	pthread_t	philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;
	
} t_philo;


int	validate_args(int argc, char **argv);
int	*convert_to_int(int argc, char **argv);
int	initialise_setup(t_philo *philo);
int	make_philo_and_call_routine(t_philo *philo);

// Elements of routine
int	make_philo_and_call_routine(t_philo *philo);
int	grab_right_fork(pthread_mutex_t *right_fork);
int	grab_left_fork(pthread_mutex_t *left_fork);
int	release_right_fork(pthread_mutex_t *right_fork);
int	release_left_fork(pthread_mutex_t *left_fork);
int	eat(void);
int	philo_sleep(void);
int	think(void);

#endif