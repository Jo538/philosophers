/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 15:28:32 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->lock)))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for lock");
		return (-1);
	}
	if (philo->is_dead)
	{
		if (pthread_mutex_unlock(&(philo->lock)))
		{
			printf("%s\n", "Error: pthread_mutex_unlock failed for lock");
			return (-1);
		}
		return (1);
	}
	if (pthread_mutex_unlock(&(philo->lock)))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for lock");
		return (-1);
	}
	return (0);
}

static int	has_eaten_enough(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->lock2)))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for lock");
		return (-1);
	}
	if (philo->number_of_meals_eaten == philo->number_of_times_must_eat)
	{
		if (pthread_mutex_unlock(&(philo->lock2)))
		{
			printf("%s\n", "Error: pthread_mutex_unlock failed for lock");
			return (-1);
		}
		return (1);		
	}
	if (pthread_mutex_unlock(&(philo->lock2)))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for lock");
		return (-1);
	}
	return (0);
}

// how do I communicate an error happening in the routine back to make_philo_and_call_routine?
static void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philo) || has_eaten_enough(philo))
			return (NULL);
		grab_right_fork(philo);
		grab_left_fork(philo);
		eat(philo);
		release_right_fork(philo);
		release_left_fork(philo);
		philo_sleep_and_think(philo);				
	}
	return (NULL);
}

static void	*routine_monitor(void *arg)
{
	long	timestamp = 0;
	t_philo *philo;

	philo = (t_philo *)arg;

	while (1)
	{
		if (has_eaten_enough(philo))
			return (NULL);
		timestamp = log_timestamp(philo) - philo->time_last_meal;
		if (timestamp >= philo->time_to_die)
		{
			if (pthread_mutex_lock(&(philo->lock)))
			{
				printf("%s\n", "Error: pthread_mutex_lock failed for lock");
				return (NULL);
			}
			philo->is_dead = 1;
			if (pthread_mutex_unlock(&(philo->lock)))
			{
				printf("%s\n", "Error: pthread_mutex_unlock failed for lock");
				return (NULL);
			}
			//printf("%ld ms: philo %d died\n", timestamp, philo->id);
			break ;
		}
	}	
	return (NULL);
}

int	launch_monitor(t_philo *philo)
{
	if (pthread_create(&(philo->monitor), NULL, routine_monitor, philo))
	{
		printf("%s\n", "Error: pthread_create failed");
		return (1);
	}
	return (0);	
}

int	launch(t_philo *philo)
{
	if (launch_monitor(philo))
		return (1);
	if (pthread_create(&(philo->philo), NULL, routine, philo))
	{
		printf("%s\n", "Error: pthread_create failed");
		return (1);
	}
	return (0);
}
