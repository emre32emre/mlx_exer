/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 15:43:41 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void myclear(t_vars *vars)
{
	for(int i = 0; i < WIDTH ;i++)
	{
		for(int j = 0; j < HEIGHT; j++)
		{
			my_mlx_pixel_put(vars,i,j,0x000000);
		}
	}
}

void printf_kadran(t_vars *vars)
{
	
	mlx_string_put(vars->m.mlx,vars->m.win,50,10,0xFFFFFF,"AUDI RS6");
	mlx_string_put(vars->m.mlx,vars->m.win,550,10,0xFFFFFF,"Gaz -> W");

	 mlx_string_put(vars->m.mlx,vars->m.win,400,600,0xFFFFFF,"00");
	 mlx_string_put(vars->m.mlx,vars->m.win,300,500,0xFFFFFF,"30");
	 mlx_string_put(vars->m.mlx,vars->m.win,280,400,0xFFFFFF,"60");
	 mlx_string_put(vars->m.mlx,vars->m.win,290,300,0xFFFFFF,"90");
	 mlx_string_put(vars->m.mlx,vars->m.win,370,200,0xFFFFFF,"120");
	 mlx_string_put(vars->m.mlx,vars->m.win,475,170,0xFFFFFF,"150");
	 mlx_string_put(vars->m.mlx,vars->m.win,600,200,0xFFFF00,"180");
	 mlx_string_put(vars->m.mlx,vars->m.win,680,300,0xFF0000,"200");
	
}
int handle_loop(t_vars *vars)
{
	//mlx_clear_window(vars->m.mlx, vars->m.win);
	myclear(vars);
	//vars->angle += 5;
	ft_draw(vars);
	
	if (vars->ispress)
		{
			if(vars->angle/ 2 > 0 && vars->angle / 2 < 100)
				vars->angle += 3;
			else if(vars->angle/ 2 >= 100 && vars->angle/ 2 <= 180)
				vars->angle += 2;
			else
				vars->angle+= 1;
		}
	if(vars->angle > 45)
	{
		
		if(vars->ispress == 0)
		{
			// usleep(2000);
			vars->angle-=5;
		}
	}
	
	mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
	printf_kadran(vars);
	return 1;	
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	
	if (argc == 2)
	{
		vars = &(t_vars){0};
		(void)argv;
		ft_vars_init(vars);

		ft_hooks(vars);
		mlx_do_key_autorepeatoff(vars->m.mlx);
		mlx_loop_hook(vars->m.mlx,handle_loop,vars);
		mlx_loop(vars->m.mlx);
	}
	write(2, "Usage: ./fdf <filename>\n", 24);
	return (0);
}



