/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkocabas <mkocabas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:47:14 by vparlak           #+#    #+#             */
/*   Updated: 2023/09/19 17:53:19 by mkocabas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_swap_origins(t_point *point_1, t_point *point_2)
{
	int	is_steep;
	int	temp;

	is_steep = ft_abs(point_2->y - point_1->y)
		> ft_abs(point_2->x - point_1->x);
	if (is_steep)
	{
		temp = point_1->x;
		point_1->x = point_1->y;
		point_1->y = temp;
		temp = point_2->x;
		point_2->x = point_2->y;
		point_2->y = temp;
	}
	if (point_1->x > point_2->x)
	{
		temp = point_1->x;
		point_1->x = point_2->x;
		point_2->x = temp;
		temp = point_1->y;
		point_1->y = point_2->y;
		point_2->y = temp;
	}
	return (is_steep);
}

static void	ft_draw_pixel(int x, int y, float brightness, t_vars *vars)
{
	int	offset;
	
	if(vars->isGodMode && vars->angle > 240)
	{
		offset = y * (vars->size_line) + x * ((vars->bpp) / 8);
		vars->data_addr[offset] = 0xFF * brightness;
		vars->data_addr[offset + 1] = 0x1A * brightness;
		vars->data_addr[offset + 2] = 0x00 * brightness;
	}
	else if(vars->angle >= 180)
	{
		offset = y * (vars->size_line) + x * ((vars->bpp) / 8);
		vars->data_addr[offset] = 0x00 * brightness;
		vars->data_addr[offset + 1] = 0x00 * brightness;
		vars->data_addr[offset + 2] = 0xFF * brightness;
	}
	else{
		offset = y * (vars->size_line) + x * ((vars->bpp) / 8);
		vars->data_addr[offset] = 0xFF * brightness;
		vars->data_addr[offset + 1] = 0xFF * brightness;
		vars->data_addr[offset + 2] = 0xFF * brightness;
	}
	
	


}

static void	ft_draw_pixel_loop(int is_steep, float intery, int x, t_vars *vars)
{
	if (is_steep)
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery), x, ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(ft_ipart(intery) + 1, x, ft_fpart(intery), vars);
	}
	else
	{
		if (ft_rfpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery), ft_rfpart(intery), vars);
		if (ft_fpart(intery) != 0)
			ft_draw_pixel(x, ft_ipart(intery) + 1, ft_fpart(intery), vars);
	}
}

static void	ft_draw_loop(t_point p1, t_point p2, int is_steep, t_vars *vars)
{
	int		x;
	float	gradient;
	float	intery;

	gradient = (float)(p2.y - p1.y) / (p2.x - p1.x);
	intery = p1.y + gradient;
	x = p1.x + 1;
	while (x <= p2.x)
	{
		ft_draw_pixel_loop(is_steep, intery, x, vars);
		intery += gradient;
		x++;
	}
}

void	ft_draw_line(t_point point_1, t_point point_2, t_vars *vars)
{
	int		is_steep;

	is_steep = ft_swap_origins(&point_1, &point_2);
	point_1.brightness = 1;
	point_2.brightness = 1;
	if (is_steep)
		ft_draw_pixel(point_1.y, point_1.x, 1, vars);
	else
		ft_draw_pixel(point_1.x, point_1.y, 1, vars);
	if (is_steep)
		ft_draw_pixel(point_2.y, point_2.x, 1, vars);
	else
		ft_draw_pixel(point_2.x, point_2.y, 1, vars);
	ft_draw_loop(point_1, point_2, is_steep, vars);
}
