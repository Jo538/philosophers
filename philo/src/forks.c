/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:38:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 11:24:02 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	grab_right_fork(t_philo *philo)
{
	int			id;
	long		timestamp;
	t_global	*global;

	id = philo->id;
	global = philo->global;
	if (pthread_mutex_lock(&(global->forks[id - 1])))
		return (error("Error: pthread_mutex_lock failed for right fork", 1));
	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);
}

int	grab_left_fork(t_philo *philo)
{
	int			id;
	long		timestamp;
	t_global	*global;

	id = philo->id;
	global = philo->global;
	if (id == global->number_of_philosphers)
	{
		if (pthread_mutex_lock(&(global->forks[0])))
			return (error("Error: pthread_mutex_lock failed for left fork", 1));		
	}
	if (pthread_mutex_lock(&(global->forks[id])))
		return (error("Error: pthread_mutex_lock failed for left fork", 1));
	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);		
}

int	release_right_fork(t_philo *philo)
{
	int			id;
	t_global	*global;

	id = philo->id;
	global = philo->global;
	if (pthread_mutex_unlock(&(global->forks[id - 1])))
		return (error("Error: pthread_mutex_unlock failed for right fork", 1));
	return (0);
}

int	release_left_fork(t_philo *philo)
{
	int			id;
	t_global	*global;

	id = philo->id;
	global = philo->global;
	if (id == global->number_of_philosphers)
	{
		if (pthread_mutex_unlock(&(global->forks[0])))
			return (error("Error: pthread_mutex_unlock failed for left fork", 1));		
	}
	if (pthread_mutex_unlock(&(global->forks[id])))
		return (error("Error: pthread_mutex_unlock failed for right fork", 1));
	return (0);	
}
