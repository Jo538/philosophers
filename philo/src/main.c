/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:08:01 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 11:38:41 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global	*global;
	t_philo		*philo;

	if (log_start_time(global))
		return (1);
	if (validate_args(argc, argv))
		return (1);
	if (setup(argv, &philo, &global))
		return (1);
	if (launch(philo))
		return (1);
	if (clean_setup(philo))
		return (1);
	return (0);
}
