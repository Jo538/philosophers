/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 15:57:09 by admin            ###   ########.fr       */
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
	printf("%s\n", "Right fork created");
	printf("%s\n", "Left fork created");
	return (0);
}

int	initialise_setup(t_philo *philo)
{
	if (make_forks(philo))
	{
		pthread_join(philo->philo, NULL);
		return (1);
	}
	return (0);
}

int	clean_setup(t_philo *philo)
{
	if (pthread_join(philo->philo, NULL))
	{
		printf("%s\n", "Error: pthread_join failed");
		return (1);
	}	
	if (pthread_mutex_destroy(&(philo->right_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}	
	if (pthread_mutex_destroy(&(philo->left_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}
	return (0);
}