/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:06:19 by admin             #+#    #+#             */
/*   Updated: 2026/06/06 18:19:06 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + ((char)str[i] - '0');
		i++;
	}
	return (sign * num);
}

int	*convert_to_int(int argc, char **argv)
{
	int	i;
	int	size;
	int	*array;

	size = argc - 1;
	array = malloc(size * sizeof(int));
	if (!array)
	{
		printf("%s\n", "Error: Malloc");
		return (NULL);
	}
	memset(array, '\0', size * sizeof(int));
	i = 0;
	while (i < size)
	{
		array[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	return (array);
}