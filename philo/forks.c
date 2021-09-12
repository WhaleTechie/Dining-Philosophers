/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:05:25 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:05:27 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*take_forks(t_phil *phil)
{
	size_t	ts;

	pthread_mutex_lock(&phil->pars->forks[phil->lfork]);
	pthread_mutex_lock(&phil->pars->forks[phil->rfork]);
	pthread_mutex_lock(&phil->pars->message);
	ts = phil_time();
	printf("%zu %d has taken a fork\n", (ts - phil->pars->start), phil->name);
	pthread_mutex_unlock(&phil->pars->message);
	pthread_mutex_lock(&phil->pars->message);
	printf("%zu %d has taken a fork\n", ts - phil->pars->start, phil->name);
	pthread_mutex_unlock(&phil->pars->message);
	return ((void *)0);
}

void	*put_forks(t_phil *ph)
{
	size_t	ts;

	ts = phil_time();
	pthread_mutex_lock(&ph->pars->message);
	printf("%zu %d is sleeping\n", ts - ph->pars->start, ph->name);
	pthread_mutex_unlock(&ph->pars->message);
	pthread_mutex_unlock(&ph->pars->forks[ph->lfork]);
	pthread_mutex_unlock(&ph->pars->forks[ph->rfork]);
	ft_sleep(ph->pars->slp);
	return ((void *)0);
}

void	destroy_forks(pthread_mutex_t *forks, t_all *pars)
{
	int	i;

	i = 0;
	while (i < pars->n_ph)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

pthread_mutex_t	*init_forks(t_all *pars)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * pars->n_ph);
	if (!forks)
		return (0);
	while (i < pars->n_ph)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
