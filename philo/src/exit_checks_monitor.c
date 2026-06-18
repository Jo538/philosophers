/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checks_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:26 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 13:45:55 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	time_since_last_meal(t_philo *philo)
{
	t_global	*global;
	long		timestamp;

	global = philo->global;
	pthread_mutex_lock(&global->lock_time_last_meal);
	timestamp = log_timestamp(global) - philo->time_last_meal;
	pthread_mutex_unlock(&global->lock_time_last_meal);
	return (timestamp);
}

static int	is_dead(t_philo *philo)
{
	if (time_since_last_meal(philo) >= philo->global->time_to_die)
		return (1);
	return (0);
}

int	monitor_death(t_philo *philo)
{
	t_global	*global;
	int			i;

	global = philo->global;
	i = 0;
	while (i < global->number_of_philosphers)
	{
		if (is_dead(&philo[i]))
		{
			pthread_mutex_lock(&global->lock_print);
			pthread_mutex_lock(&global->lock_is_dead);
			if (!global->is_dead)
			{
				printf("%ld %d died\n", log_timestamp(global), philo[i].id);
				global->is_dead = 1;
			}
			pthread_mutex_unlock(&global->lock_is_dead);
			pthread_mutex_unlock(&global->lock_print);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	has_eaten_enough(t_philo *philo)
{
	t_global	*global;
	int			done;

	global = philo->global;
	if (global->number_of_times_must_eat < 0)
		return (0);
	pthread_mutex_lock(&global->lock_number_of_meals_eaten);
	done = (philo->number_of_meals_eaten >= global->number_of_times_must_eat);
	pthread_mutex_unlock(&global->lock_number_of_meals_eaten);
	return (done);
}

int	monitor_eating(t_philo *philo)
{
	t_global	*global;
	int			i;
	int			count;

	global = philo->global;
	if (global->number_of_times_must_eat < 0)
		return (0);
	i = 0;
	count = 0;
	while (i < global->number_of_philosphers)
	{
		if (has_eaten_enough(&philo[i]))
			count++;
		i++;
	}
	if (count == global->number_of_philosphers)
	{
		pthread_mutex_lock(&global->lock_have_eaten_enough);
		global->have_eaten_enough = 1;
		pthread_mutex_unlock(&global->lock_have_eaten_enough);
		return (1);
	}
	return (0);
}
