/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 13:01:47 by mrakotos          #+#    #+#             */
/*   Updated: 2026/04/30 19:14:50 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTION_H
#define PROJECTION_H

#include "../minilibx-linux/mlx.h"

#define WIN_H 800
#define WIN_W 800
#define WIN_TITLE "cub3D"

typedef struct test_s
{
	void* mlx_ptr;
	void* windows_ptr;
	unsigned char** map;
	float cellX;
	float cellY;
	int mapSizeX;
	int mapSizeY;
	void* img;
	char* addr;
	int bpp;
	int line_length;
	int endian;
} t_test;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

int init(t_test* data_ptr);
void draw(t_test* data);

#endif
