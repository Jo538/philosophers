/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:26 by admin             #+#    #+#             */
/*   Updated: 2026/06/16 12:23:54 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	is_dead_routine(t_param *param)
{
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;
	if (pthread_mutex_lock(&(global->lock)))
		return (error("Error: pthread_mutex_lock failed for lock", -1));		
	if (philo->is_dead)
	{
		if (pthread_mutex_unlock(&(global->lock)))
			return (error("Error: pthread_mutex_unlock failed for lock", -1));
		return (1);
	}
	if (pthread_mutex_unlock(&(global->lock)))
		return (error("Error: pthread_mutex_unlock failed for lock", -1));
	return (0);
}

int	is_dead_monitor(t_param *param)
{
	long	timestamp;
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;
	timestamp = log_timestamp(global) - philo->time_last_meal;
	if (timestamp >= global->time_to_die)
	{
		if (pthread_mutex_lock(&(global->lock)))
			return (error("Error: pthread_mutex_lock failed for lock", -1));
		philo->is_dead = 1;
		if (pthread_mutex_unlock(&(global->lock)))
			return (error("Error: pthread_mutex_unlock failed for lock", -1));
		printf("%ld ms: philo %d died\n", timestamp, philo->id);
		return (1);
	}	
	return (0);
}

int	has_eaten_enough(t_param *param)
{
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;
	if (pthread_mutex_lock(&(global->lock2)))
		return (error("Error: pthread_mutex_lock failed for lock", -1));
	if (philo->number_of_meals_eaten == global->number_of_times_must_eat)
	{
		if (pthread_mutex_unlock(&(global->lock2)))
			return (error("Error: pthread_mutex_unlock failed for lock", -1));
		return (1);		
	}
	if (pthread_mutex_unlock(&(global->lock2)))
		return (error("Error: pthread_mutex_unlock failed for lock", -1));
	return (0);
}
