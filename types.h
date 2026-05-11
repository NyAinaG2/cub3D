/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrakotos <mrakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 09:01:01 by mrakotos          #+#    #+#             */
/*   Updated: 2026/05/11 11:04:49 by mrakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#define WIN_W 720
#define WIN_H 360
#define WIN_TITLE "cub3D"
#define TILE_SIZE 64
#define ROTATION_SPEED 0.001
#define MOVE_SPEED 0.001
#define PI2 6.28
#include <sys/time.h>

typedef struct s_move
{
	int rotate_left;
	int rotate_right;
	int forward;
	int backward;
	int left;
	int right;
} t_move;

typedef struct test_s
{
	t_move move;
	void* mlx_ptr;
	void* windows_ptr;
	unsigned char** map;
	int tile_size;
	float playerX;
	float playerY;
	float direction;
	float playerR;
	float fovMax;
	float fovMin;
	float fov;
	float step;
	float cellX;
	float cellY;
	double game_time;
	int wall_color;
	int ceil_color;
	int floor_color;
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

typedef struct s_vec
{
	t_point delta;
	t_point side;
	t_point angle;
	t_point step;
	t_point res;
	float t;
	int mapX;
	int mapY;
	int hit;
} t_vec;

typedef struct s_dda
{
	t_point hitP;
	t_point sideD;
	float distance;
	int side;
} t_dda;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

#endif
