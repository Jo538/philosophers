/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 14:17:56 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_forks(t_philo *philo)
{
	if (pthread_mutex_init(&(philo->right_fork), NULL))
	{
		printf("%s\n", "Error: pthread_mutex_init failed for right fork");
		return (1);		
	}
	if (pthread_mutex_init(&(philo->left_fork), NULL))
	{
		printf("%s\n", "Error: pthread_mutex_init failed for left fork");
		pthread_mutex_destroy(&(philo->right_fork));
		return (1);		
	}
	return (0);
}

int	initialise_setup(char **argv, t_philo *philo)
{
	philo->id = 1;
	philo->is_dead = 0;	
	convert_to_int(argv, philo);
	if (pthread_mutex_init(&(philo->lock), NULL))
	{
		printf("%s\n", "Error: pthread_mutex_init failed for lock");
		return (1);		
	}
	if (make_forks(philo))
		return (1);
	return (0);
}
