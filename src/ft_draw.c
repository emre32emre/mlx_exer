/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:05:37 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 17:50:02 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>



void	orjin_delta(t_point *point, int orjin_x, int orjin_y)
{
	point->x = point->x + orjin_x;
	point->y = point->y + orjin_y;
}

t_point	ft_rotation_2d(t_point p1, int teta)
{
	t_point	tmp_point;

	teta %= 360;

	tmp_point.x =  - (p1.y * sin(teta * (M_PI / 180)));
	tmp_point.y =  + (p1.y * cos(teta * (M_PI / 180)));
	return(tmp_point);
}

#include <stdio.h>
void	ft_draw(t_vars *vars)
{
	//km
	t_point	point_1;
	t_point	point_4;
	//rpm
	

	point_1.x = 500;
	point_1.y = 400;
	point_4.x = 500;
	point_4.y = 600;
		//ft_draw_line(point_1, point_4, vars);
	point_4.x = point_4.x - point_1.x;
	point_4.y = point_4.y - point_1.y;
	point_4 = ft_rotation_2d(point_4, vars->angle);
	point_4.x = point_4.x + point_1.x;
	point_4.y = point_4.y + point_1.y;
	ft_draw_line(point_1, point_4, vars);
	point_1.x+=1;
	point_4.x+=1;
	ft_draw_line(point_1, point_4, vars);
	point_1.x+=1;
	point_4.x+=1;
	ft_draw_line(point_1, point_4, vars);

}
