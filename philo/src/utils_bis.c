/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:17:22 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 15:03:55 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg, int to_ret)
{
	printf("%s\n", msg);
	return (to_ret);
}

void	destroy_locks(t_global *g, int count)
{
	if (count > 4)
		pthread_mutex_destroy(&g->lock_number_of_meals_eaten);
	if (count > 3)
		pthread_mutex_destroy(&g->lock_time_last_meal);
	if (count > 2)
		pthread_mutex_destroy(&g->lock_have_eaten_enough);
	if (count > 1)
		pthread_mutex_destroy(&g->lock_is_dead);
	if (count > 0)
		pthread_mutex_destroy(&g->lock_print);
}

static int	clean_global(t_global *g)
{
	int	i;

	i = 0;
	if (pthread_join(g->monitor, NULL))
		return (error("Error: join", 1));
	while (i < g->number_of_philosphers)
	{
		pthread_mutex_destroy(&g->forks[i]);
		i++;
	}
	destroy_locks(g, 5);
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
			return (error("Error: join", 1));
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
