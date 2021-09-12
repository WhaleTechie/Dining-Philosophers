/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:05:37 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:05:39 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(char **argv, t_all *ph_info)
{
	ph_info->n_ph = ft_atoi(argv[1]);
	ph_info->die = ft_atoi(argv[2]);
	ph_info->eat = ft_atoi(argv[3]);
	ph_info->slp = ft_atoi(argv[4]);
	if (ph_info->n_ph == 0 || ph_info->die < 60 || ph_info->eat < 60 || \
	ph_info->slp < 60)
		return (str_error ("Error: wrong arguments\n"));
	if (argv[5])
	{
		ph_info->n_eat = ft_atoi(argv[5]);
		if (ph_info->n_eat == 0)
			return (str_error("Error: number of minimal meals cannot be 0!\n"));
	}
	pthread_mutex_init(&ph_info->message, NULL);
	return (0);
}

void	init_phls(t_phil *ph_all, t_all *pars)
{
	int	i;

	pthread_mutex_init(&pars->mexit, NULL);
	pthread_mutex_lock(&pars->mexit);
	i = 0;
	while (i < pars->n_ph)
	{
		ph_all[i].name = i + 1;
		ph_all[i].n_meals = 0;
		ph_all[i].lfork = i;
		ph_all[i].rfork = (i + 1) % pars->n_ph;
		ph_all[i].pars = pars;
		i++;
	}
}

int	dining(t_phil	*ph)
{
	int	i;

	i = 0;
	while (i < ph->pars->n_ph)
	{
		ph[i].last_eat = phil_time();
		ph[i].is_dead = 0;
		if (pthread_create(&ph[i].tid, NULL, &ph_rout, (void *)&ph[i]) != 0)
			return (str_error("Error: in creating threads\n"));
		usleep(100);
		i++;
	}
	if (pthread_create(&ph->pars->mntr, NULL, monitor, (void *)ph) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_phil	*ph;
	t_all	pars;

	if ((argc < 5) || (argc > 6))
		return (str_error("Error: bad arguments\n"));
	if (check_isdigit(argv) != 0)
		return (str_error("Error: bad arguments\n"));
	if (get_data(argv, &pars) != 0)
		return (-1);
	ph = malloc(sizeof(t_phil) * pars.n_ph);
	pars.forks = init_forks(&pars);
	init_phls(ph, &pars);
	pars.start = phil_time();
	if (dining(ph) != 0)
		return (str_error("No dinner today\n"));
	pthread_join(ph->pars->mntr, NULL);
	pthread_mutex_lock(&ph->pars->mexit);
	destroy_forks(pars.forks, &pars);
	pthread_mutex_destroy(&ph->pars->mexit);
	pthread_mutex_destroy(&ph->pars->message);
	return (0);
}
