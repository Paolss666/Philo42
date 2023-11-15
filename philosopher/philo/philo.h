/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:01 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/16 17:04:42 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <math.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
	number_of_philosophers 
	time_to_die 
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]
*/

typedef struct s_data	t_data;
typedef struct s_info
{
	pthread_t	philosopher;
	int			id;
	int			left_fork;
	int			right_fork;
	int			eat_count;
	long		last_eat;
	t_data		*link_table;
}				t_info;

typedef struct s_data
{
	t_info			**link_philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				must_eat;
	int				stop_flag;
	long			time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	last_ate;
}				t_data;

// --------- UTILS PHILO ---------- ///
int			ft_atoi(const char *nptr);
long		get_time(long time);
void		get_fork(t_info *philo, int fork);
int			even_fork(int fork, t_info *philo);
void		*routine(void *args);
int			ft_operate(t_info *philo);
int			take_fork(t_info *philo);
void		mutex_printf(char *string, t_info *philo, int color);
void		ft_monitoring_mutex(t_data *table);
void		all_mutex_destroy(t_data *table);
int			msleep(int time, t_info *philo);
int			check_stop_flag(t_info *philo);
void		run_philo(t_data *table);
int			ft_creat_thread(t_data *table, t_info **philo);
int			ft_check_args(char **av);

// --------- ACTION ---------- ///
int			eating(t_info *philo);
int			sleeping(t_info *philo);
int			thinking(t_info *philo);

// --------- INIT STACK ---------- ///
void		parsing(int ac, char **av, t_data *table);
int			check_data(int ac, char **av, t_data *table);
int			init_mutex(t_data *table);
void		init_philo(int i, t_info *philo, t_data *table);

#endif