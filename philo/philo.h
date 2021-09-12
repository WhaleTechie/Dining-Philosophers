/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrinova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:05:56 by lkrinova          #+#    #+#             */
/*   Updated: 2021/08/09 15:05:58 by lkrinova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_all
{
	int				n_ph;
	int				die;
	int				eat;
	int				slp;
	int				n_eat;
	size_t			start;
	pthread_t		mntr;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	mexit;
}					t_all;

typedef struct s_phil
{
	int				name;
	int				n_meals;
	int				lfork;
	int				rfork;
	int				is_dead;
	pthread_t		tid;
	size_t			last_eat;
	t_all			*pars;
}					t_phil;

int				ft_strlen(char *str);
int				str_error(char *str);
int				ft_atoi(const char *str);
int				check_isdigit(char **argv);
int				get_data(char **argv, t_all *ph_info);
void			init_phls(t_phil *ph_all, t_all *pars);
int				dining(t_phil	*ph);
size_t			phil_time(void);
void			*ph_rout(void *args);
void			*eat(t_phil *phil);
void			ft_sleep(size_t ms);
void			*monitor(void *args);
int				check_death(t_phil *ph, int num);
int				check_meals(t_phil *ph, int num, int n_meals);
pthread_mutex_t	*init_forks(t_all *pars);
void			*take_forks(t_phil *phil);
void			*put_forks(t_phil *ph);
void			destroy_forks(pthread_mutex_t *forks, t_all *pars);
#endif
