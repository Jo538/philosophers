/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:09:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	log_last_meal(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_mutex_lock(&(global->lock_time_last_meal)))
		return (error("Error: pthread_mutex_lock failed for lock_time_last_meal", 1));
	philo->time_last_meal = log_timestamp(global);
	if (pthread_mutex_unlock(&(global->lock_time_last_meal)))
		return (error("Error: pthread_mutex_unlock failed for lock_time_last_meal", 1));
	return (0);
}

int	eat(t_philo *philo)
{
	t_global	*global;

	global = philo->global;

	if (log_last_meal(philo))
		return (1);
	printf("%ld ms: philo %d is eating\n", philo->time_last_meal, philo->id);
	if (usleep(global->time_to_eat * 1000))
		return (error("Error: usleep failed for eating", 1));
	if (pthread_mutex_lock(&(global->lock_number_of_meals_eaten)))
		return (error("Error: pthread_mutex_lock failed for lock2", 1));
	philo->number_of_meals_eaten++;
	if (pthread_mutex_unlock(&(global->lock_number_of_meals_eaten)))
		return (error("Error: pthread_mutex_unlock failed for lock2", 1));
	monitor_eating(philo->philos);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	long	timestamp;
	t_global	*global;

	global = philo->global;

	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is sleeping\n", timestamp, philo->id);
	if (usleep(global->time_to_sleep * 1000))
		return (error("Error: usleep failed for sleeping", 1));
	return (0);
}

int	ft_think(t_philo *philo)
{
	long	timestamp;
	t_global	*global;

	global = philo->global;
	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is thinking\n", timestamp, philo->id);
	return (0);	
}
