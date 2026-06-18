/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:06:40 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	release_forks(t_philo *philo, int release_right, int release_left)
{
	if (release_right == 1)
		release_right_fork(philo);
	if (release_left == 1)
		release_left_fork(philo);
	return (0);
}

static int	grab_forks(t_philo *philo)
{
	int	id;

	id = philo->id;
	if (id % 2 == 1)
	{
		if (grab_right_fork(philo))
			return (release_forks(philo, 1, 0), 1);
		if (grab_left_fork(philo))
			return (release_forks(philo, 1, 1), 1);	
	}
	if (id % 2 == 0)
	{
		if (grab_left_fork(philo))
			return (release_forks(philo, 0, 1), 1);
		if (grab_right_fork(philo))
			return (release_forks(philo, 1, 1), 1);		
	}
	return (0);
}

// how do I communicate an error happening in the routine back to make_philo_and_call_routine?
static void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead_routine(philo) || have_eaten_enough_routine(philo))
			return (NULL);
		if (grab_forks(philo))
			return (NULL);
		eat(philo);
		release_right_fork(philo);
		release_left_fork(philo);
		if (is_dead_routine(philo))
			return (NULL);
		ft_sleep(philo);
		if (is_dead_routine(philo))
			return (NULL);
		ft_think(philo);			
	}
	return (NULL);
}

static void	*routine_monitor(void *arg)
{
	long	timestamp = 0;
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (monitor_eating(philo))
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
		if (pthread_create(&(philo[i].philo), NULL, routine, &philo[i]))
			return (error("Error: pthread_create failed", 1));
		i++;			
	}
	return (0);
}

int	launch(t_philo *philo)
{
	t_global	*global;

	global = philo->global;

	if (pthread_create(&(global->monitor), NULL, routine_monitor, philo))
		return (error("Error: pthread_create failed", 1));
	launch_routine(philo);
	return (0);
}
