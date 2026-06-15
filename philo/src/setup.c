/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 22:06:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_forks(t_philo *philo)
{
	if (pthread_mutex_init(&(philo->right_fork), NULL))
		return (error("Error: pthread_mutex_init failed for right fork", 1));
	if (pthread_mutex_init(&(philo->left_fork), NULL))
		return (error("Error: pthread_mutex_init failed for left fork", 1));
	return (0);
}

int	initialise_setup(char **argv, t_param *param)
{
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;
	
	philo->id = 1;
	philo->is_dead = 0;
	philo->number_of_meals_eaten = 0;	
	convert_to_int(argv, global);
	if (pthread_mutex_init(&(global->lock), NULL))
		return (error("Error: pthread_mutex_init failed for lock", 1));
	if (pthread_mutex_init(&(global->lock2), NULL))
		return (error("Error: pthread_mutex_init failed for lock2", 1));
	if (make_forks(philo))
		return (1);
	return (0);
}
