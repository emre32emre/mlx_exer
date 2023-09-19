/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:53:27 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 17:45:15 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>




void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
void draw_hollow_circle(t_vars *data, int origin_x, int origin_y, int radius, int line_thickness, int color)
{
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            if (x * x + y * y >= (radius - line_thickness) * (radius - line_thickness) &&
                x * x + y * y <= radius * radius)
            {
                int draw_x = origin_x + x;
                int draw_y = origin_y + y;

                if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
                {
                    my_mlx_pixel_put(data, draw_x, draw_y, color);
                }
            }
        }
    }
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
	char str[20];
	int speed = (int)vars->angle - 45;
	sprintf(str,"%d",speed);
	

	 mlx_string_put(vars->m.mlx,vars->m.win,750,10,0xFFFFFF,"Speed:");
	 mlx_string_put(vars->m.mlx,vars->m.win,810,10,0xFFFFFF,str);
	if(speed > 200)
	{
	 	mlx_string_put(vars->m.mlx,vars->m.win,750,30,0xFFFFFF,"Nitro Avaiable");
		
	}
	mlx_string_put(vars->m.mlx,vars->m.win,750,810,0xFFFFFF,"Gas -> W");
	mlx_string_put(vars->m.mlx,vars->m.win,750,830,0xFFFFFF,"Brake -> S");
	mlx_string_put(vars->m.mlx,vars->m.win,750,850,0xFFFFFF,"HandBrake -> Space");
	mlx_string_put(vars->m.mlx,vars->m.win,750,870,0xFFFFFF,"Nitro -> Q");
	

	 mlx_string_put(vars->m.mlx,vars->m.win,400,600,0xFFFFFF,"00");
	 mlx_string_put(vars->m.mlx,vars->m.win,300,500,0xFFFFFF,"30");
	 mlx_string_put(vars->m.mlx,vars->m.win,280,400,0xFFFFFF,"60");
	 mlx_string_put(vars->m.mlx,vars->m.win,290,300,0xFFFFFF,"90");
	 mlx_string_put(vars->m.mlx,vars->m.win,370,200,0xFFFFFF,"120");
	 mlx_string_put(vars->m.mlx,vars->m.win,475,170,0xFFFFFF,"150");
	 mlx_string_put(vars->m.mlx,vars->m.win,600,200,0xFFFF00,"180");
	 mlx_string_put(vars->m.mlx,vars->m.win,680,300,0xFF0000,"200");
	 if(vars->ishandbrake && vars->angle > 45)
	 {
	 	mlx_string_put(vars->m.mlx,vars->m.win,205,607,0xFFFF00,"ABS");
		
	 }

	 if(vars->ispress && vars->isGodMode && vars->angle >240)
	 {
		mlx_string_put(vars->m.mlx,vars->m.win,795,607,0x001AFF,"NITRO");
		}

	
	
}
int handle_loop(t_vars *vars)
{
	//mlx_clear_window(vars->m.mlx, vars->m.win);
	myclear(vars);
	//vars->angle += 5;
	ft_draw(vars);
	
	printf("angle ->%f\n",vars->angle);
	draw_hollow_circle(vars,500,400,250,3,0xFFFFFF);
	if (vars->ispress)
	{
			
			if(vars->angle > 0 && vars->angle < 100)
			{
				vars->angle += 1.5;
				draw_hollow_circle(vars,500,400,250,3,0xFFFFFF);
			}
			else if(vars->angle >= 100 && vars->angle <= 180)
			{
				vars->angle += 1.2;
				draw_hollow_circle(vars,500,400,250,3,0xFFD000);
				draw_hollow_circle(vars,500,400,260,3,0xFFD000);
			}
			else if(vars->angle >= 180 && vars->angle <= 210)
			{
				vars->angle += 0.8;
				draw_hollow_circle(vars,500,400,250,3,0xFF0000);
				draw_hollow_circle(vars,500,400,260,3,0xFF0000);
			}
			else 
			{
				vars->angle += 0.2;
				draw_hollow_circle(vars,500,400,250,3,0xFF0000);
				draw_hollow_circle(vars,500,400,260,3,0xFF0000);
				draw_hollow_circle(vars,500,400,270,3,0xFF0000);
			}
			if(vars->angle > 200)
			{
				draw_hollow_circle(vars,500,400,250,3,0xFF0000);
				draw_hollow_circle(vars,500,400,260,3,0xFF0000);
				draw_hollow_circle(vars,500,400,270,3,0xFF0000);
				draw_hollow_circle(vars,500,400,280,3,0xFF0000);
			}
	}
	if(vars->angle > 45 && !vars->ispress)
	{
		
		
				draw_hollow_circle(vars,500,400,250,3,0xFFFFFF);
			if(vars->angle > 0 && vars->angle < 100)
			{
				vars->angle -= 0.5;
			}
			else if(vars->angle >= 100 && vars->angle <= 180)
			{
				vars->angle -= 1;

			}
			else	
			{
					vars->angle -= 0.6;

			}
	}
	if(vars->isbrake)
	{
		if(vars->angle > 45)
			vars->angle -= 1.8;
	}
	//draw_hollow_circle(vars,220,620,30,3,0xFF0000);
	if(vars->ishandbrake)
	{
		if(vars->angle > 45)
		{
			draw_hollow_circle(vars,220,620,30,2,0xFF0000);
			draw_hollow_circle(vars,220,620,38,3,0xFF0000);
			
			vars->angle -= 4.8;
		}
	}
	if(vars->ispress && vars->isGodMode && vars->angle > 240)
	{
		draw_hollow_circle(vars,500,400,250,3,0x001AFF);
		draw_hollow_circle(vars,500,400,260,3,0x001AFF);
		draw_hollow_circle(vars,500,400,270,3,0x001AFF);
		draw_hollow_circle(vars,500,400,280,3,0x001AFF);
		draw_hollow_circle(vars,500,400,290,3,0x001AFF);
		draw_hollow_circle(vars,500,400,300,3,0x001AFF);
		draw_hollow_circle(vars,500,400,310,3,0x001AFF);
		draw_hollow_circle(vars,500,400,320,3,0x001AFF);
		
		draw_hollow_circle(vars,820,620,40,2,0x001AFF);
		vars->angle += 5.5;
	}
	mlx_put_image_to_window(vars->m.mlx, vars->m.win, vars->img_ptr, 0, 0);
	printf_kadran(vars);
	return 1;	
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	

	
		vars = &(t_vars){0};
		(void)argv;
		ft_vars_init(vars);

		ft_hooks(vars);
		//mlx_do_key_autorepeatoff(vars->m.mlx);
		mlx_loop_hook(vars->m.mlx,handle_loop,vars);
		mlx_loop(vars->m.mlx);

	return (0);
}



