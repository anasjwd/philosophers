/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:44:59 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/17 22:37:41 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_is_over(void)
{
	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	return (0);
}

int	next_fork(unsigned int number, int num_of_philos)
{
	return (number % num_of_philos);
}

void	put_curr_state(int philo_number, char *msg)
{
	int	curr_time;

	curr_time = get_time_from_start();
	printf("%d %d %s\n", curr_time, philo_number, msg);
}

int	ft_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;
	int	temp;

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	first_fork = philo->number - 1;
	second_fork = next_fork(philo->number, (*simulation_data())->num_of_philos);
	if ((unsigned)(philo->number + 1) == (*simulation_data())->num_of_philos)
	{
		temp = first_fork;
		first_fork = second_fork;
		second_fork = temp;
	}

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);

	pthread_mutex_lock((*simulation_data())->philos[first_fork]->fork);

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);

	put_curr_state(philo->number, "has taken a fork");

	pthread_mutex_lock((*simulation_data())->philos[second_fork]->fork);

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);

	put_curr_state(philo->number, "has taken a fork");

	put_curr_state(philo->number, "is eating");

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);

	pthread_mutex_lock(philo->state_mutex);
	philo->num_of_meals++;
	philo->last_meal_time = get_time_from_start();
	pthread_mutex_unlock(philo->state_mutex);

	usleep((*simulation_data())->time_to_eat * 1000);

	pthread_mutex_unlock((*simulation_data())->philos[first_fork]->fork);
	pthread_mutex_unlock((*simulation_data())->philos[second_fork]->fork);

	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	put_curr_state(philo->number, "is sleeping");
	usleep((*simulation_data())->time_to_sleep * 1000);

	return (0);
}

int	ft_think(t_philo *philo)
{
	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	put_curr_state(philo->number, "is thinking");
	return (0);
}
