/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:18:19 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 17:05:49 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	ft_close_x(t_vars *vars)
{
	ft_free_map(vars);
	mlx_destroy_image(vars->m.mlx, vars->img_ptr);
	mlx_destroy_window(vars->m.mlx, vars->m.win);
	exit(EXIT_SUCCESS);
	return (1);
}

static int	ft_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_free_map(vars);
		mlx_destroy_image(vars->m.mlx, vars->img_ptr);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == 13) {
		//write(1,"down",5);
		vars->ispress = 1;
	}
	if(keycode == 1)
	{
		vars->isbrake = 1;
	}
	if(keycode == 49)
	{
		vars->ishandbrake = 1;
	}
	if(keycode == 12)
	{
		vars->isGodMode = 1;
	}

	
	return (1);
}
static int	ft_key_relase(int keycode, t_vars *vars)
{
	if (keycode == 13) {
		//write(1,"up",3);
		vars->ispress = 0;
	}
	if(keycode == 1)
	{
		vars->isbrake = 0;
	}
	if(keycode == 49)
	{
		vars->ishandbrake = 0;
	}
	if(keycode == 12)
	{
		vars->isGodMode = 0;
	}

	return (1);
}

void	ft_hooks(t_vars *vars)
{
	mlx_hook(vars->m.win, 2, 1L << 0, ft_close, vars);
	mlx_hook(vars->m.win, 17, 1L << 17, ft_close_x, vars);
	mlx_hook(vars->m.win, 3, 1L << 17, ft_key_relase, vars);
}

void	ft_vars_init(t_vars	*vars)
{
	vars->m.mlx = mlx_init();
	if (!vars->m.mlx)
	{
		perror("Graphical server connecting error");
		ft_free_map(vars);
		exit(EXIT_FAILURE);
	}
	vars->m.win = mlx_new_window(vars->m.mlx, WIDTH, HEIGHT, "FdF");
	if (!vars->m.win)
	{
		perror("Window initializing error");
		ft_free_map(vars);
		exit(EXIT_FAILURE);
	}
	vars->img_ptr = mlx_new_image(vars->m.mlx, WIDTH, HEIGHT);
	if (!vars->img_ptr)
	{
		perror("Image initializing error");
		ft_free_map(vars);
		mlx_destroy_window(vars->m.mlx, vars->m.win);
		exit(EXIT_FAILURE);
	}
	vars->data_addr = mlx_get_data_addr(vars->img_ptr,
			&vars->bpp, &vars->size_line, &vars->endian);
	vars->angle = 20;
	vars->ispress = 0;
	vars->isbrake = 0;
	vars->ishandbrake = 0;
	vars->isGodMode = 0;
}
