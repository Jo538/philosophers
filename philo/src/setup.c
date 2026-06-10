/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 12:24:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_forks(pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	if (pthread_mutex_init(right_fork, NULL))
	{
		printf("%s\n", "Error: pthread_mutex_init failed for right fork");
		return (1);		
	}
	if (pthread_mutex_init(left_fork, NULL))
	{
		printf("%s\n", "Error: pthread_mutex_init failed for left fork");
		pthread_mutex_destroy(right_fork);
		return (1);		
	}
	printf("%s\n", "Right fork created");
	printf("%s\n", "Left fork created");
	return (0);
}
void *worker(void *arg) 
{
    int id = *(int *)arg;
    return NULL;
}

int	make_philo(pthread_t *philo)
{
	int			id;

	id = 1;
	if (pthread_create(philo, NULL, worker, &id))
	{
		printf("%s\n", "Error: pthread_create failed");
		return (1);
	}
	printf("%s\n", "philo created");
	return (0);
}

int	initialise_setup(void)
{
	int			id;
	pthread_t	philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	left_fork;

	if (make_philo(&philo))
		return (1);
	if (make_forks(&right_fork, &left_fork))
	{
		pthread_join(philo, NULL);
		return (1);
	}
	return (0);
}

int	clean_setup(pthread_t *philo, pthread_mutex_t *right_fork, pthread_mutex_t *left_fork)
{
	if (pthread_join(*philo, NULL))
	{
		printf("%s\n", "Error: pthread_join failed");
		return (1);
	}	
	if (pthread_mutex_destroy(right_fork))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}	
	if (pthread_mutex_destroy(left_fork))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}
	return (0);
}