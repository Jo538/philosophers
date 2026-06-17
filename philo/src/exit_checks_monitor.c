/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checks_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:26 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 18:05:44 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int	time_since_last_meal(t_philo *philo)
{
	long		timestamp;
	t_global	*global;

	global = philo->global;

	if (pthread_mutex_lock(&(global->lock_time_last_meal)))
		return (error("Error: pthread_mutex_lock failed for lock_time_last_meal", -1));
	timestamp = log_timestamp(global) - philo->time_last_meal;
	if (pthread_mutex_unlock(&(global->lock_time_last_meal)))
		return (error("Error: pthread_mutex_unlock failed for lock_time_last_meal", -1));
	return (timestamp);	
}

static int	is_dead(t_philo *philo)
{
	long		timestamp;
	t_global	*global;

	global = philo->global;
	timestamp = time_since_last_meal(philo);
	if (timestamp >= global->time_to_die)
	{		
		printf("%ld ms: philo %d died\n", timestamp, philo->id);
		return (1);
	}	
	return (0);
}

int	monitor_death(t_philo *philo)
{
	int			i;
	t_global	*global;

	i = 0;
	global = philo->global;
	while (i < global->number_of_philosphers)
	{
		if (is_dead(&philo[i]))
		{
			if (pthread_mutex_lock(&(global->lock_is_dead)))
				return (error("Error: pthread_mutex_lock failed for lock_is_dead", 1));
			global->is_dead = 1;
			if (pthread_mutex_unlock(&(global->lock_is_dead)))
				return (error("Error: pthread_mutex_unlock failed for lock_is_dead", 1));
			return (0);
		}
		i++;
	}
	return (0);
}

static int	has_eaten_enough(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_mutex_lock(&(global->lock_number_of_meals_eaten)))
		return (error("Error: pthread_mutex_lock failed for lock", -1));
	if (philo->number_of_meals_eaten == global->number_of_times_must_eat)
	{
		if (pthread_mutex_unlock(&(global->lock_number_of_meals_eaten)))
			return (error("Error: pthread_mutex_unlock failed for lock", -1));
		return (1);		
	}
	if (pthread_mutex_unlock(&(global->lock_number_of_meals_eaten)))
		return (error("Error: pthread_mutex_unlock failed for lock", -1));
	return (0);
}

int	monitor_eating(t_philo *philo)
{
	int			i;
	int			count;
	t_global	*global;

	i = 0;
	count = 0;
	global = philo->global;
	while (i < global->number_of_philosphers)
	{
		if (has_eaten_enough(&philo[i]))
			count++;
		i++;
	}
	if (count == global->number_of_philosphers)
	{
		if (pthread_mutex_lock(&(global->lock_have_eaten_enough)))
			return (error("Error: pthread_mutex_lock failed for llock_have_eaten_enough", 1));
		global->have_eaten_enough = 1;	
		if (pthread_mutex_unlock(&(global->lock_have_eaten_enough)))
			return (error("Error: pthread_mutex_unlock failed for lock_have_eaten_enough", 1));
	}	
	return (0);
}
