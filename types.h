/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:01:01 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/03 09:01:58 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#define WIN_W 1280
#define WIN_H 720
#define WIN_TITLE "cub3D"
#define TILE_SIZE 64
#define ROTATION_SPEED 0.1
#define MOVE_SPEED 0.2
#define PI2 6.28

typedef struct test_s
{
	void* mlx_ptr;
	void* windows_ptr;
	unsigned char** map;
	int tile_size;
	float playerX;
	float playerY;
	float direction;
	float playerR;
	int offsetX;
	int offsetY;
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

typedef struct s_point
{
	float x;
	float y;
} t_point;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

#endif