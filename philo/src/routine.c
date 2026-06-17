/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 11:41:53 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// how do I communicate an error happening in the routine back to make_philo_and_call_routine?
static void	*routine(void *arg)
{
	t_param		*param;
	t_philo		*philo;
	t_global	*global;

	param = (t_param *)arg;
	philo = param->philo;
	global = &param->global;
	printf("test: %d\n", philo->id);
	while (1)
	{
		if (is_dead_routine(param) || has_eaten_enough(param))
			return (NULL);
		grab_right_fork(param);
		grab_left_fork(param);
		eat(param);
		release_right_fork(philo);
		release_left_fork(philo);
		if (is_dead_routine(param))
			return (NULL);
		ft_sleep(param);
		if (is_dead_routine(param))
			return (NULL);
		ft_think(param);			
	}
	return (NULL);
}

static void	*routine_monitor(void *arg)
{
	long	timestamp = 0;
	t_param		*param;
	t_philo		*philo;
	t_global	*global;

	param = (t_param *)arg;
	philo = param->philo;
	global = &param->global;
	while (1)
	{
		if (has_eaten_enough(param))
			return (NULL);
		if (is_dead_monitor(param))
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
