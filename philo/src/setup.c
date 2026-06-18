/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:25:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:45:50 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_global *global)
{
	int	i;
	int	size;

	size = global->number_of_philosphers;
	global->forks = malloc(size * sizeof(pthread_mutex_t));
	if (!global->forks)
		return (error("Error: malloc", 1));
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&global->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&global->forks[i]);
			free(global->forks);
			global->forks = NULL;
			return (error("Error: fork init", 1));
		}
		i++;
	}
	return (0);
}

static int	init_locks(t_global *g)
{
	if (pthread_mutex_init(&g->lock_print, NULL))
		return (0);
	if (pthread_mutex_init(&g->lock_is_dead, NULL))
		return (1);
	if (pthread_mutex_init(&g->lock_have_eaten_enough, NULL))
		return (2);
	if (pthread_mutex_init(&g->lock_time_last_meal, NULL))
		return (3);
	if (pthread_mutex_init(&g->lock_number_of_meals_eaten, NULL))
		return (4);
	return (5);
}

static void	destroy_forks_array(t_global *g)
{
	int	i;

	i = 0;
	while (i < g->number_of_philosphers)
	{
		pthread_mutex_destroy(&g->forks[i]);
		i++;
	}
	free(g->forks);
	g->forks = NULL;
}

static int	setup_global(char **argv, t_global **global)
{
	t_global	*g;
	int			n;

	g = *global;
	g->is_dead = 0;
	g->have_eaten_enough = 0;
	g->forks = NULL;
	convert_to_int(argv, global);
	if (init_forks(g))
		return (1);
	n = init_locks(g);
	if (n < 5)
	{
		destroy_locks(g, n);
		destroy_forks_array(g);
		return (error("Error: lock init", 1));
	}
	return (0);
}

int	setup(char **argv, t_philo **philo, t_global **global)
{
	int	i;
	int	size;

	*philo = NULL;
	if (setup_global(argv, global))
		return (1);
	size = (*global)->number_of_philosphers;
	*philo = malloc(size * sizeof(t_philo));
	if (!*philo)
	{
		destroy_locks(*global, 5);
		destroy_forks_array(*global);
		return (error("Error: malloc", 1));
	}
	i = 0;
	while (i < size)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].time_last_meal = 0;
		(*philo)[i].number_of_meals_eaten = 0;
		(*philo)[i].global = *global;
		(*philo)[i].philos = philo;
		i++;
	}
	return (0);
}
