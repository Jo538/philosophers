/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checks_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:26 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 18:07:31 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	is_dead_routine(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_mutex_lock(&(global->lock_is_dead)))
		return (error("Error: pthread_mutex_lock failed for lock", -1));		
	if (global->is_dead)
	{
		if (pthread_mutex_unlock(&(global->lock_is_dead)))
			return (error("Error: pthread_mutex_unlock failed for lock_is_dead", -1));
		return (1);
	}
	if (pthread_mutex_unlock(&(global->lock_is_dead)))
		return (error("Error: pthread_mutex_unlock failed for lock_is_dead", -1));
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

int	have_eaten_enough_routine(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_mutex_lock(&(global->lock_have_eaten_enough)))
		return (error("Error: pthread_mutex_lock failed for lock_have_eaten_enough", -1));
	if (global->have_eaten_enough == 1)
	{
		if (pthread_mutex_unlock(&(global->lock_have_eaten_enough)))
			return (error("Error: pthread_mutex_unlock failed for lock_have_eaten_enough", -1));
		return (1);	
	}
	if (pthread_mutex_unlock(&(global->lock_have_eaten_enough)))
		return (error("Error: pthread_mutex_unlock failed for lock_have_eaten_enough", -1));
	return (0);
}
