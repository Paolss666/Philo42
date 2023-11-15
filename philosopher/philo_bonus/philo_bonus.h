/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:01 by npaolett          #+#    #+#             */
/*   Updated: 2023/11/07 18:27:27 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo
{
	int				num_philos;
	int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				t_think;
	int				s_eat;
	int				s_sleep;
	int				s_think;
	int				s_fork1;
	int				s_fork2;
	int				num_eat;
	int				num_eat_count;
	int				stop_flag;
	int				died;
	int				*pid;
	sem_t			*block_printf;
	sem_t			*block_fork;
	sem_t			*block_variable;
	sem_t			*block_time;
	sem_t			*block_eat;
	sem_t			*block_sleep_think;
	long long int	t_start;
	int				index;
	long long int	t_meal;
	pthread_t		check_monitor;
}					t_philo;

// ---------- INIT PHILO -------------- //
t_philo				*init_philo(int ac, char **av);
void				exit_philo(t_philo **philo);
int					ft_atoi_modif(const char *str);
// ---------- UTILS PRINT-------------- //
void				print_fork(t_philo *philo);
void				print_fork2(t_philo *philo);
void				print_eat(t_philo *philo);
void				print_sleeping(t_philo *philo);
void				print_think(t_philo *philo);
void				ft_print_check(t_philo *philo);
void				philo_printf(t_philo *philo, char *str);
// ---------- UTILS -------------- //
int					ft_error(char *s, t_philo *philo);
long long			find_time(void);
void				*check_monitor(void *args);
void				m_sleep(long long time, t_philo *philo);
void				exit_philo_2(t_philo *philo);
void				ft_post_all_sem(t_philo *philo);
int					ft_check_args(char **av);
void				stop_flag_died(t_philo *philo);
void				stop_flag_eat(t_philo *philo);
void				philo_start(t_philo *philo);
/*
	number_of_philosophers 
	time_to_die 
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]
*/

#endif
