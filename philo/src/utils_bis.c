/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:17:22 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:46:29 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg, int to_ret)
{
	printf("%s\n", msg);
	return (to_ret);
}

static int	clean_forks(t_global *global)
{
	int	i;
	int	size;

	i = 0;
	size = global->number_of_philosphers;
	while (i < size)
	{
		if (pthread_mutex_destroy(&(global->forks[i])))
			return (error("Error: pthread_mutex_destroy failed for lock", 1));
		i++;		
	}
	return (0);
}

static int	clean_global(t_global *global)
{
	if (pthread_join(global->monitor, NULL))
		return (error("Error: pthread_join failed", 1));
	if (clean_forks(global))
		return (1);
	if (pthread_mutex_destroy(&(global->lock_is_dead)))
		return (error( "Error: pthread_mutex_destroy failed for lock", 1));
	if (pthread_mutex_destroy(&(global->lock_time_last_meal)))
		return (error( "Error: pthread_mutex_destroy failed for lock_time_last_meal", 1));
	if (pthread_mutex_destroy(&(global->lock_number_of_meals_eaten)))
		return (error("Error: pthread_mutex_destroy failed for lock_number_of_meals_eaten", 1));
	if (pthread_mutex_destroy(&(global->lock_have_eaten_enough)))
		return (error( "Error: pthread_mutex_destroy failed for lock_eaten_enough", 1));
	return (0);
}

static int	clean_philo(t_philo *philo)
{
	int	i;
	int	size;

	i = 0;
	size = philo->global->number_of_philosphers;
	while (i < size)
	{
		if (pthread_join(philo[i].philo, NULL))
			return (error("Error: pthread_join failed", 1));
		i++;		
	}
	return (0);	
}

int	clean_setup(t_philo *philo)
{
	clean_philo(philo);
	clean_global(philo->global);
	free(philo->global->forks);
	free(philo);
	return (0);
}
