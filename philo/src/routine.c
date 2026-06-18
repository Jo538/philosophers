/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 15:01:02 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	grab_forks_pair(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (grab_right_fork(philo))
			return (1);
		if (grab_left_fork(philo))
		{
			release_right_fork(philo);
			return (1);
		}
	}
	else
	{
		if (grab_left_fork(philo))
			return (1);
		if (grab_right_fork(philo))
		{
			release_left_fork(philo);
			return (1);
		}
	}
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	t_global	*global;

	global = philo->global;
	if (global->number_of_philosphers == 1)
	{
		if (grab_right_fork(philo))
			return (1);
		usleep(global->time_to_die * 1000);
		release_right_fork(philo);
		return (1);
	}
	return (grab_forks_pair(philo));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->global->time_to_eat * 500);
	while (1)
	{
		if (is_dead_routine(philo) || have_eaten_enough_routine(philo))
			return (NULL);
		if (grab_forks(philo))
			return (NULL);
		eat(philo);
		release_right_fork(philo);
		release_left_fork(philo);
		if (is_dead_routine(philo) || have_eaten_enough_routine(philo))
			return (NULL);
		ft_sleep(philo);
		if (is_dead_routine(philo) || have_eaten_enough_routine(philo))
			return (NULL);
		ft_think(philo);
	}
	return (NULL);
}
