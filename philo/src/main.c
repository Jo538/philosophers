/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:08:01 by admin             #+#    #+#             */
/*   Updated: 2026/06/07 20:50:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	*array_of_ints;

	if (!validate_args(argc, argv))
		return (1);
	array_of_ints = convert_to_int(argc, argv);
	return (0);
}
