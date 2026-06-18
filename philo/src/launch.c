/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:30:00 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 15:30:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (have_eaten_enough_routine(philo))
			return (NULL);
		if (monitor_death(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static int	launch_routine(t_philo *philo)
{
	int	i;
	int	size;

	size = philo->global->number_of_philosphers;
	i = 0;
	while (i < size)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, &philo[i]))
			return (error("Error: pthread_create", 1));
		i++;
	}
	return (0);
}

int	launch(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (pthread_create(&global->monitor, NULL, routine_monitor, philo))
		return (error("Error: pthread_create", 1));
	if (launch_routine(philo))
		return (1);
	return (0);
}
