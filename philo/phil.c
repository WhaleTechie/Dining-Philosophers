/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:05:01 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:05:03 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	phil_time(void)
{
	struct timeval	mytime;

	gettimeofday(&mytime, NULL);
	return (mytime.tv_sec * 1000 + mytime.tv_usec / 1000);
}

int	is_dead(t_phil *ph)
{
	if (ph->is_dead == 1)
		return (1);
	if (phil_time() - ph->last_eat >= (unsigned long)ph->pars->die)
	{
		if (ph->is_dead == 0)
		{
			ph->is_dead = 1;
			pthread_mutex_lock(&ph->pars->message);
			printf("%lu %d died\n", phil_time() - \
			ph->pars->start, ph->name);
			pthread_mutex_unlock(&ph->pars->mexit);
			usleep(100);
		}
		return (1);
	}
	return (0);
}

int	check_death(t_phil *ph, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (is_dead(&ph[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_meals(t_phil *ph, int num, int n_meals)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (ph[i].n_meals < n_meals)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *args)
{
	t_phil	*ph;
	int		i;

	i = 0;
	ph = (t_phil *)args;
	while (1)
	{
		while (i < ph->pars->n_ph)
		{
			if (check_death(ph, ph->pars->n_ph))
				return ((void *)0);
			if (ph->pars->n_eat > 0 \
			&& check_meals(ph, ph->pars->n_ph, ph->pars->n_eat))
			{
				pthread_mutex_lock(&ph->pars->message);
				ft_sleep(5);
				printf("All ate well at least %d times\n", ph->pars->n_eat);
				pthread_mutex_unlock(&ph->pars->mexit);
				return ((void *)0);
			}
		}
	}
}
