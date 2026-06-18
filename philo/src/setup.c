/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 11:00:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	setup_forks(t_global *global)
{
	int	i;
	int	size;

	size = global->number_of_philosphers;
	global->forks = malloc(size * sizeof(pthread_mutex_t));
	if (!global->forks)
		return (error("Error: malloc failed", 1));
	memset(global->forks, '\0', size * sizeof(pthread_mutex_t));
	i = 0;		
	while (i < size)
	{
		if (pthread_mutex_init(&(global->forks[i]), NULL))
			return (error("Error: pthread_mutex_init failed for right fork", 1));	
		i++;	
	}
	return (0);	
}

static int	setup_global(char **argv, t_global **global)
{
	(*global)->is_dead = 0;
	(*global)->have_eaten_enough = 0;
	convert_to_int(argv, global);
	if (setup_forks(*global))
		return (1);
	if (pthread_mutex_init(&((*global)->lock_is_dead), NULL))
		return (error("Error: pthread_mutex_init failed for lock_is_dead", 1));
	if (pthread_mutex_init(&((*global)->lock_have_eaten_enough), NULL))
		return (error("Error: pthread_mutex_init failed for lock_have_eaten_enough", 1));
	if (pthread_mutex_init(&((*global)->lock_time_last_meal), NULL))
		return (error("Error: pthread_mutex_init failed for lock_time_last_meal", 1));
	if (pthread_mutex_init(&((*global)->lock_number_of_meals_eaten), NULL))
		return (error("Error: pthread_mutex_init failed for lock_number_of_meals_eaten", 1));
	return (0);	
}

static int	setup_philo(t_philo **philo, t_global **global)
{
	int	i;
	int	size;

	size = (*global)->number_of_philosphers;
	*philo = malloc(size * sizeof(t_philo));
	if (!*philo)
		return (error("Error: malloc failed", 1));
	memset(*philo, '\0', size * sizeof(t_philo));
	i = 0;		
	while (i < size)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].number_of_meals_eaten = 0;
		(*philo)[i].global = *global;
		i++;	
	}
	return (0);	
}

int	setup(char **argv, t_philo **philo, t_global **global)
{		
	if (setup_global(argv, global))
		return (1);
	if (setup_philo(philo, global))
		return (1);
	return (0);
}
