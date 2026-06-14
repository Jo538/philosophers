/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/14 19:03:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// how do I communicate an error happening in the routine back to make_philo_and_call_routine?
static void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	grab_right_fork(philo);
	grab_left_fork(philo);
	eat(philo);
	release_right_fork(philo);
	release_left_fork(philo);
	philo_sleep_and_think(philo);
	return (NULL);
}

static void	*routine_monitor(void *arg)
{
	long	timestamp = 0;
	t_philo *philo;

	philo = (t_philo *)arg;

	while (1)
	{
		timestamp = log_timestamp(philo) - philo->time_last_meal;
		if (timestamp >= philo->time_to_die)
		{
			printf("%ld ms: philo %d died\n", timestamp, philo->id);
			break ;
		}
	}	
	return (NULL);
}

int	launch_monitor(t_philo *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, routine_monitor, philo))
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
