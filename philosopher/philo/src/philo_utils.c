/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npaolett <npaolett@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:13:27 by npaolett          #+#    #+#             */
/*   Updated: 2023/10/13 14:46:37 by npaolett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	parity;

	number = 0;
	parity = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			parity++;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = 10 * number + nptr[i] - 48;
		i++;
	}
	if (parity % 2 == 0)
		return (number);
	return (-number);
}

long	get_time(long time)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - time);
}

void	run_philo(t_data *table)
{
	t_info	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_info *) * table->philo_num);
	if (!philo)
		return (free(philo));
	if (ft_creat_thread(table, philo) == 0)
	{
		ft_monitoring_mutex(table);
		i = -1;
		while (++i < table->philo_num)
		{
			pthread_join(philo[i]->philosopher, NULL);
			free(philo[i]);
		}
	}
	all_mutex_destroy(table);
	free(table->link_philo);
	free(table->fork);
	free(philo);
}

/*
Pour chaque philosophe, vous saisissez des informations 
et créez ensuite chaque philosophe 
comme un fil qui exécute une fonction de routine.
Pendant que les threads exécutent les fonctions de routine,
Le thread principal observe l'état des threads 
en exécutant une fonction de surveillance. */

/*
À l'intérieur de la fonction de routine, 
nous retardons la progression en endormant les 
philosophes un nombre pair de fois afin 
d'empêcher les threads d'y accéder en même temps.
*/

/*
Verifica se l'ID del filosofo (philo->id) 
è pari o dispari utilizzando l'operatore bitwise AND & con 1. 
Se l'ID è pari (cioè il bit meno significativo è 0), 
la funzione chiama	usleep(1000), 
che sospende il thread corrente per 1000 microsecondi 
(1 millisecondo). 
Questa pausa potrebbe essere utilizzata per sincronizzare 
l'inizio delle 
attività dei filosofi in modo che i filosofi con 
ID pari inizino leggermente più tardi 
rispetto a quelli con ID dispari.
Entra in un ciclo while infinito 
(while (1)) che chiaramente rappresenta l'esecuzione continua del thread.
*/

void	*routine(void *args)
{
	t_info	*philo;

	philo = args;
	if (!(philo->id & 1))
		usleep(philo->link_table->time_to_eat);
	while (1)
		if (ft_operate(philo) == 0)
			break ;
	return (0);
}

/*
    if (take_fork(philo)): 
	Cette ligne semble être une condition vérifiant 
	si la fonction ou la méthode
	take_fork renvoie une valeur différente de zéro.
	Si c'est le cas, cela signifie que le philosophe a réussi 
	à prendre les fourchettes 
	(une ressource) nécessaires pour manger.

    if (eating(philo)):
	Si la fonction take_fork renvoie vrai (différent de zéro),
	alors cette ligne vérifie si la fonction ou la
	méthode eating renvoie une valeur différente de zéro.
	Si c'est le cas, cela signifie que le philosophe a réussi à manger.

    if (sleeping(philo)):
	Suivant la même logique, cette ligne vérifie si 
	la fonction ou la méthode sleeping
	renvoie une valeur différente de zéro.
	Si c'est le cas, cela signifie que le philosophe a réussi à dormir.

    if (thinking(philo)):
	Encore une fois, cette ligne vérifie si la fonction
	ou la méthode
	thinking renvoie une valeur différente de zéro.
	Si c'est le cas, cela signifie que le philosophe 
	a réussi à réfléchir.

    Enfin, return (1); 
	est utilisé pour indiquer une exécution
	réussie de toutes les tâches (prendre des fourchettes,
	manger, dormir et réfléchir) dans l'ordre.
	Si toutes ces tâches se terminent avec succès, la fonction renvoie 1.

    Si l'une des conditions des instructions if échoue,
	la fonction n'atteindra pas l'instruction return (1);
	et elle se terminera avec une valeur de retour de 0,
	indiquant qu'une tâche dans la séquence a échoué.
	
*/

int	ft_operate(t_info *philo)
{
	if (take_fork(philo))
		if (eating(philo))
			if (sleeping(philo))
				if (thinking(philo))
					return (1);
	return (0);
}
