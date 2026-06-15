/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 22:27:47 by admin            ###   ########.fr       */
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
	philo = &param->philo;
	global = &param->global;
	while (1)
	{
		if (is_dead(param) || has_eaten_enough(param))
			return (NULL);
		grab_right_fork(param);
		grab_left_fork(param);
		eat(param);
		release_right_fork(philo);
		release_left_fork(philo);
		ft_sleep(param);				
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
	philo = &param->philo;
	global = &param->global;
	while (1)
	{
		if (has_eaten_enough(param))
			return (NULL);
		timestamp = log_timestamp(global) - philo->time_last_meal;
		if (timestamp >= global->time_to_die)
		{
			if (pthread_mutex_lock(&(global->lock)))
				return (error("Error: pthread_mutex_lock failed for lock", 1), NULL);
			philo->is_dead = 1;
			if (pthread_mutex_unlock(&(global->lock)))
				return (error("Error: pthread_mutex_unlock failed for lock", 1), NULL);
			printf("%ld ms: philo %d died\n", timestamp, philo->id);
			break ;
		}
		usleep(5000);
	}	
	return (NULL);
}

int	launch(t_param *param)
{
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;

	if (pthread_create(&(global->monitor), NULL, routine_monitor, philo))
		return (error("Error: pthread_create failed", 1));
	if (pthread_create(&(philo->philo), NULL, routine, philo))
		return (error("Error: pthread_create failed", 1));
	return (0);
}
