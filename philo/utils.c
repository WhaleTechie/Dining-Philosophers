/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:05:13 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:05:16 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	str_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	k;

	i = 0;
	x = 0;
	k = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == 45 || str[i] == '+')
	{
		if (str[i] == 45)
			k = -1;
		i++;
	}
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		x = x * 10 + (str[i] - 48);
		i++;
	}
	return (x * k);
}

int	check_isdigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_sleep(size_t ms)
{
	size_t	start;
	size_t	end;

	start = phil_time();
	end = start + ms;
	while (phil_time() < end)
		usleep(100);
}
