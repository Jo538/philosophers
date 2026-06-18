/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:17:29 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 11:42:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_positive_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	are_positive_ints(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_positive_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_values(char **argv)
{
	int	i;

	if (ft_atoi(argv[1]) < 1)
		return (0);
	i = 2;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 1)
			return (0);
		i++;
	}
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (0);
	return (1);
}

int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error("Error: bad argc", 1));
	if (!are_positive_ints(argv))
		return (error("Error: bad argv format", 1));
	if (!check_values(argv))
		return (error("Error: arg values out of range", 1));
	return (0);
}
