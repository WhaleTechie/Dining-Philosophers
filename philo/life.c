/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:04:46 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:04:51 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*eat(t_phil *phil)
{
	size_t	ts;

	ts = phil_time();
	phil->last_eat = phil_time();
	pthread_mutex_lock(&phil->pars->message);
	printf("%zu %d is eating\n", ts - phil->pars->start, phil->name);
	phil->n_meals++;
	pthread_mutex_unlock(&phil->pars->message);
	ft_sleep(phil->pars->eat);
	return ((void *)0);
}

void	*ph_rout(void	*phils)
{
	size_t	ts;
	t_phil	*phil;

	ts = phil_time();
	phil = (t_phil *)phils;
	while (1)
	{
		take_forks(phil);
		eat(phil);
		put_forks(phil);
		pthread_mutex_lock(&phil->pars->message);
		ts = phil_time();
		printf("%zu %d is thinking\n", ts - phil->pars->start, phil->name);
		pthread_mutex_unlock(&phil->pars->message);
	}
	return ((void *)0);
}
