/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:46:12 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	log_last_meal(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_mutex_lock(&global->lock_time_last_meal))
		return (error("Error: lock", 1));
	philo->time_last_meal = log_timestamp(global);
	if (pthread_mutex_unlock(&global->lock_time_last_meal))
		return (error("Error: unlock", 1));
	return (0);
}

static void	smart_sleep(t_philo *philo, long ms)
{
	long	start;

	start = log_timestamp(philo->global);
	while (log_timestamp(philo->global) - start < ms)
	{
		if (is_dead_routine(philo))
			return ;
		usleep(200);
	}
}

int	eat(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (log_last_meal(philo))
		return (1);
	print_status(philo, "is eating");
	smart_sleep(philo, global->time_to_eat);
	if (pthread_mutex_lock(&global->lock_number_of_meals_eaten))
		return (error("Error: lock", 1));
	philo->number_of_meals_eaten++;
	if (pthread_mutex_unlock(&global->lock_number_of_meals_eaten))
		return (error("Error: unlock", 1));
	monitor_eating(*philo->philos);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo, philo->global->time_to_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	t_global	*g;
	long		delay;

	g = philo->global;
	print_status(philo, "is thinking");
	delay = (g->time_to_die - g->time_to_eat - g->time_to_sleep) / 2;
	if (delay > 0)
		smart_sleep(philo, delay);
	return (0);
}
