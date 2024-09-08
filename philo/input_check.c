/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarakur <ykarakur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 11:49:01 by ykarakur          #+#    #+#             */
/*   Updated: 2024/09/07 12:35:40 by ykarakur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	numbers_check(char *user_input)
{
	int	k;

	k = 0;
	if (user_input[k] == '-')
		return (1);
	if (user_input[k] == '+')
	{
		if (user_input[k + 1] < '0' || user_input[k + 1] > '9')
			return (1);
	}
	while (user_input[k])
	{
		if (user_input[k] == '\0')
			break ;
		else if ((user_input[k] >= '0' && user_input[k] <= '9'))
			k++;
		else
			return (1);
	}
	return (0);
}

int	p_atoi(char *str)
{
	int	k;
	int	number;

	k = 0;
	number = 0;
	if (str[k] == '+')
		k++;
	while (str[k] >= '0' && str[k] <= '9')
		number = number * 10 + str[k++] - 48;
	return (number);
}

int	check_av(char **av)
{
	int	k;

	k = 1;
	if (!av[k])
		return (1);
	while (av[k])
	{
		if (numbers_check(av[k]) == 1)
			return (1);
		k++;
	}
	return (0);
}
