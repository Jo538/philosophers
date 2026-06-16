/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/16 19:07:01 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	setup_global(char **argv, t_global *global)
{
	convert_to_int(argv, global);
	if (pthread_mutex_init(&(global->lock_is_dead), NULL))
		return (error("Error: pthread_mutex_init failed for lock_is_dead", 1));
	if (pthread_mutex_init(&(global->lock_time_last_meal), NULL))
		return (error("Error: pthread_mutex_init failed for lock_time_last_meal", 1));
	if (pthread_mutex_init(&(global->lock_number_of_meals_eaten), NULL))
		return (error("Error: pthread_mutex_init failed for lock_number_of_meals_eaten", 1));
	return (0);	
}

static t_philo	*setup_philo(t_global *global)
{
	int	i;
	int	size;
	t_philo	*philo;

	size = global->number_of_philosphers + 1;
	philo = malloc(size * sizeof(t_philo));
	if (!philo)
		return (error("Error: malloc failed", 1), NULL);
	memset(philo, '\0', size * sizeof(t_philo));
	i = 0;		
	while (i < size - 1)
	{
		philo[i].id = i + 1;
		philo[i].is_dead = 0;
		philo[i].number_of_meals_eaten = 0;
		if (pthread_mutex_init(&(philo[i].right_fork), NULL))
			return (error("Error: pthread_mutex_init failed for right fork", 1), NULL);
		if (pthread_mutex_init(&(philo[i].left_fork), NULL))
			return (error("Error: pthread_mutex_init failed for left fork", 1), NULL);
		i++;	
	}
	return (philo);	
}

int	initialise_setup(char **argv, t_param *param)
{
	t_global	*global;

	global = &param->global;
		
	if (setup_global(argv, global))
		return (1);
	param->philo = setup_philo(global);
	if (!param->philo)
		return (1);
	return (0);
}
